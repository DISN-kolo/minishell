/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:17:06 by akozin            #+#    #+#             */
/*   Updated: 2024/04/16 16:24:39 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	io_dub_determinator(t_data *data, int *i, t_token *tokens, int k)
{
	if (!ft_strncmp(tokens[i[2] + i[3]].token, "<", 2))
		data->coms[i[0]].ins[k].dub = 0;
	else if (!ft_strncmp(tokens[i[2] + i[3]].token, ">", 2))
		data->coms[i[0]].outs[k].dub = 0;
	else if (!ft_strncmp(tokens[i[2] + i[3]].token, "<<", 3))
		data->coms[i[0]].ins[k].dub = 1;
	else if (!ft_strncmp(tokens[i[2] + i[3]].token, ">>", 3))
		data->coms[i[0]].outs[k].dub = 1;
}

static void	in_filler(t_data *data, int *i, t_token *ts, int k)
{
	io_dub_determinator(data, i, ts, k);
	data->coms[i[0]].ins[k++].fname = ts[i[2]++ + i[3] + 1].token;
}

static void	out_filler(t_data *data, int *i, t_token *ts, int l)
{
	io_dub_determinator(data, i, ts, l);
	data->coms[i[0]].ins[l++].fname = ts[i[2]++ + i[3] + 1].token;
}
/*
 * 1. the first part sets the dub of the current io redir.
 *   this means < or <<, > or >>.
 * 2. the second part (big if ...) fills the io arrays, and moves by
 *   two in order to skip the io filename that's already filled in.
 */
void	cmd_filler(t_data *data, int *i, t_token *ts)
{
	int	k;
	int	l;
	int	m;

	k = 0;
	l = 0;
	m = 0;
	while (++i[2] < i[4])
	{
		if (ts[i[2] + i[3]].type == REDIR)
		{
			if (!ft_strncmp(ts[i[2] + i[3]].token, "<", 2)
				|| !ft_strncmp(ts[i[2] + i[3]].token, "<<", 3))
				in_filler(data, i, ts, k);
			else if (!ft_strncmp(ts[i[2] + i[3]].token, ">", 2)
				|| !ft_strncmp(ts[i[2] + i[3]].token, ">>", 3))
				out_filler(data, i, ts, l);
		}
		else
			data->coms[i[0]].com[m++] = ts[i[2] + i[3]].token;
	}
}
