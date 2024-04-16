/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:55:17 by akozin            #+#    #+#             */
/*   Updated: 2024/04/16 16:40:39 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * is_in ==> we count the <, <<
 * !is_in => we count the >, >>
 * u = the "until" integer, because we only need to count within the command
 */
static int	ioredirs_counter(t_token *tokens, int is_in, int u)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (tokens[i].token && i < u)
	{
		printf("\t\t\tio redirs counter #%3d (<%3d) is '%s'\n", i, u, tokens[i].token);
		if (is_in)
		{
			if (!ft_strncmp(tokens[i].token, "<", 2)
				|| !ft_strncmp(tokens[i].token, "<<", 3))
				c++;
		}
		else
		{
			if (!ft_strncmp(tokens[i].token, ">", 2)
				|| !ft_strncmp(tokens[i].token, ">>", 3))
				c++;
		}
		i++;
	}
	return (c);
}

/*
 * the next part sets the corresponding (in? or out?) filename
 * we need separate indices for iterating over these arrays
 * also we need to allocate them somehow, so we need to count em all.
 */
int	io_coms_alloc(t_com *coms, t_token *tokens, int u)
{
	int	ilen;
	int	olen;

	ilen = ioredirs_counter(tokens, 1, u);
	printf("\t\tilen = %3d\n", ilen);
	olen = ioredirs_counter(tokens, 0, u);
	printf("\t\tolen = %3d\n", olen);
	coms->ins = malloc(sizeof (t_inout) * (ilen + 1));
	coms->outs = malloc(sizeof (t_inout) * (olen + 1));
	if (!coms->ins || !coms->outs)
		return (1);
	return (0);
}
