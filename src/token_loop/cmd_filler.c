/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:17:06 by akozin            #+#    #+#             */
/*   Updated: 2024/04/23 16:19:48 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		printf("i[2] = %d, i[2] + i[3] = %d, amb redir token index = %d\n", i[2], i[2]+i[3], data->amb_tok_ind);
		if (i[2] + i[3] == data->amb_tok_ind - 1)
		{
			printf("that's a good place to stop\n");
			break ;
		}
		if (ts[i[2] + i[3]].type == REDIR || ts[i[2] + i[3]].type == HDOC)
		{
			if (cmd_filler_internal(data, i, ts, k))
				return (1);
		}
		else
			data->coms[i[0]].com[j++] = ft_strdup(ts[i[2] + i[3]].token);
	}
	data->coms[i[0]].ios[k].fname = NULL;
	return (0);
}
