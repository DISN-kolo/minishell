/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:55:17 by akozin            #+#    #+#             */
/*   Updated: 2024/05/07 17:35:57 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_str_redir(char *s)
{
	if (!ft_strncmp(s, "<", 2) || !ft_strncmp(s, "<<", 3)
		|| !ft_strncmp(s, ">", 2) || !ft_strncmp(s, ">>", 3))
		return (1);
	return (0);
}

/*
 * is_in ==> we count the <, <<
 * !is_in => we count the >, >>
 * u = the "until" integer, because we only need to count within the command
 */
static int	ioredirs_counter(t_com *coms, t_token *tokens, int u)
{
	int		i;
	int		c;
	t_tok_s	prev;
	int		finished;

	i = 0;
	c = 0;
	finished = 0;
	prev = TOKEN;
	while (tokens[i].token && i < u)
	{
		c += is_str_redir(tokens[i].token);
		if (!finished && (tokens[i].type == REDIR || tokens[i].type == HDOC)
			&& (prev == REDIR || prev == HDOC))
		{
			finished = 1;
			coms->amb_redir_ind = c - 2;
		}
		prev = tokens[i].type;
		i++;
	}
	if (!finished && (prev == REDIR || prev == HDOC))
		coms->amb_redir_ind = c - 2;
	return (c);
}

/*
 * the next part sets the corresponding (in? or out?) filename
 * we need separate indices for iterating over these arrays
 * also we need to allocate them somehow, so we need to count em all.
 */
int	io_coms_alloc(t_com *coms, t_token *tokens, int u)
{
	int	iolen;

	coms->amb_redir_ind = -42;
	iolen = ioredirs_counter(coms, tokens, u);
	printf("iolen = %d\n", iolen);
	coms->ios = malloc(sizeof (t_inout) * (iolen + 1));
	if (!coms->ios)
		return (1);
	return (0);
}
