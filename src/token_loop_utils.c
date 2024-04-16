/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:55:17 by akozin            #+#    #+#             */
/*   Updated: 2024/04/16 13:24:24 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

/*
 * 1. the first part sets the dub of the current io redir.
 *   this means < or <<, > or >>.
 * 2. the second part (big if ...) fills the io arrays, and moves by
 *   two in order to skip the io filename that's already filled in.
 */
void	com_filler(t_data *data, int *i, t_token *ts)
{
	int	k;
	int	l;

	k = 0;
	l = 0;
	while (++i[2] < i[1])
	{
		if (ts[i[2] + i[3]].type == REDIR)
		{
			if (!ft_strncmp(ts[i[2] + i[3]].token, "<", 2)
				|| !ft_strncmp(ts[i[2] + i[3]].token, "<<", 3))
			{
				io_dub_determinator(data, i, ts, k);
				data->coms[i[0]].ins[k++].fname = ts[i[2]++ + i[3] + 1].token;
			}
			else if (!ft_strncmp(ts[i[2] + i[3]].token, ">", 2)
				|| !ft_strncmp(ts[i[2] + i[3]].token, ">>", 3))
			{
				io_dub_determinator(data, i, ts, l);
				data->coms[i[0]].ins[l++].fname = ts[i[2]++ + i[3] + 1].token;
			}
		}
		else
			data->coms[i[0]].com[i[2]] = ts[i[2] + i[3]].token;
	}
}
