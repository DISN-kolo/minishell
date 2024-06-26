/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_filler_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:11:35 by akozin            #+#    #+#             */
/*   Updated: 2024/05/18 14:39:25 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	io_dub_determinator(t_data *data, int *i, t_token *tokens, int k)
{
	if (!ft_strncmp(tokens[i[2] + i[3]].token, "<", 2))
		data->coms[i[0]].ios[k].dub = 0;
	else if (!ft_strncmp(tokens[i[2] + i[3]].token, ">", 2))
		data->coms[i[0]].ios[k].dub = 0;
	else if (!ft_strncmp(tokens[i[2] + i[3]].token, "<<", 3))
		data->coms[i[0]].ios[k].dub = 1;
	else if (!ft_strncmp(tokens[i[2] + i[3]].token, ">>", 3))
		data->coms[i[0]].ios[k].dub = 1;
}

/*
 * there probably is no other reason for a token to be empty at that point
 * but an empty variable substituted
 */
static int	in_filler(t_data *d, int *i, t_token *ts, int *k)
{
	d->coms[i[0]].ios[*k].in = 1;
	io_dub_determinator(d, i, ts, *k);
	d->coms[i[0]].ios[*k].fname = ft_strdup(ts[i[2] + i[3] + 1].token);
	if (!d->coms[i[0]].ios[*k].fname)
		return (1);
	(*k)++;
	i[2]++;
	return (0);
}

static int	out_filler(t_data *d, int *i, t_token *ts, int *k)
{
	d->coms[i[0]].ios[*k].in = 0;
	io_dub_determinator(d, i, ts, *k);
	d->coms[i[0]].ios[*k].fname = ft_strdup(ts[i[2] + i[3] + 1].token);
	if (!d->coms[i[0]].ios[*k].fname)
		return (1);
	(*k)++;
	i[2]++;
	return (0);
}

int	cmd_filler_internal(t_data *data, int *i, t_token *ts, int *k)
{
	if (!ft_strncmp(ts[i[2] + i[3]].token, "<", 2)
		|| !ft_strncmp(ts[i[2] + i[3]].token, "<<", 3))
	{
		if (in_filler(data, i, ts, k))
			return (1);
	}
	else if (!ft_strncmp(ts[i[2] + i[3]].token, ">", 2)
		|| !ft_strncmp(ts[i[2] + i[3]].token, ">>", 3))
	{
		if (out_filler(data, i, ts, k))
			return (1);
	}
	return (0);
}
