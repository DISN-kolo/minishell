/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:55:17 by akozin            #+#    #+#             */
/*   Updated: 2024/04/24 12:12:50 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * is_in ==> we count the <, <<
 * !is_in => we count the >, >>
 * u = the "until" integer, because we only need to count within the command
 */
static int	ioredirs_counter(t_token *tokens, int u)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (tokens[i].token && i < u)
	{
		c += (!ft_strncmp(tokens[i].token, "<", 2)
					|| !ft_strncmp(tokens[i].token, "<<", 3)
					|| !ft_strncmp(tokens[i].token, ">", 2)
					|| !ft_strncmp(tokens[i].token, ">>", 3));
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
	int	iolen;

	iolen = ioredirs_counter(tokens, u);
	coms->ios = malloc(sizeof (t_inout) * (iolen + 1));
	if (!coms->ios)
		return (1);
	return (0);
}
