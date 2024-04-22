/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:17:06 by akozin            #+#    #+#             */
/*   Updated: 2024/04/22 12:34:20 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * 1. the first part sets the dub of the current io redir.
 *   this means < or <<, > or >>.
 * 2. the second part (big if ...) fills the io arrays, and moves by
 *   two in order to skip the io filename that's already filled in.
 *
 * k[0] = k
 * k[1] = j
 * k[2] = m
 */
int	cmd_filler(t_data *data, int *i, t_token *ts)
{
	int	k[3];

	k[0] = 0;
	k[1] = 0;
	k[2] = 0;
	while (++i[2] < i[4])
	{
		if (ts[i[2] + i[3]].type == REDIR || ts[i[2] + i[3]].type == HDOC)
		{
			if (cmd_filler_internal(data, i, ts, k))
				return (1);
		}
		else
			data->coms[i[0]].com[k[2]++] = ft_strdup(ts[i[2] + i[3]].token);
	}
	data->coms[i[0]].ins[k[0]].fname = NULL;
	data->coms[i[0]].outs[k[1]].fname = NULL;
	return (0);
}
