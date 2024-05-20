/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:17:06 by akozin            #+#    #+#             */
/*   Updated: 2024/05/20 14:06:48 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	save_cmd(t_data *data, int *i, int *j, t_token *ts)
{
	data->coms[i[0]].com[*j] = ft_strdup(ts[i[2] + i[3]].token);
	if (!data->coms[i[0]].com[(*j)++])
		return (1);
	return (0);
}

/*
 * 1. the first part sets the dub of the current io redir.
 *   this means < or <<, > or >>.
 * 2. the second part (big if ...) fills the io arrays, and moves by
 *   two in order to skip the io filename that's already filled in.
 *
 * k - i/os counter
 * j - argv counter
 */
int	cmd_filler(t_data *data, int *i, t_token *ts)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (++i[2] < i[4])
	{
		if (ts[i[2] + i[3]].type == REDIR_AMB)
		{
			g_err = 1;
			i[2] = i[4];
			break ;
		}
		printf("i = { %2d, %2d, %2d, %2d, %2d}\n", i[0], i[1], i[2], i[3], i[4]);
		printf("ts[%2d].token: '%s'\n", i[2] + i[3], ts[i[2] + i[3]].token);
		if (ts[i[2] + i[3]].type == REDIR || ts[i[2] + i[3]].type == HDOC)
		{
			if (cmd_filler_internal(data, i, ts, &k))
				return (1);
		}
		else if (save_cmd(data, i, &j, ts))
			return (1);
	}
	data->coms[i[0]].ios[k].fname = NULL;
	return (0);
}
