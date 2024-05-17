/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:14:33 by akozin            #+#    #+#             */
/*   Updated: 2024/05/07 15:57:15 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cmd_count(t_token *tokens)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (tokens[i].token)
	{
		if (tokens[i].type == PIPE)
			count++;
		i++;
	}
	return (count);
}

/*
 * i[4] is used strictly for total-until-pipe len purposes, while
 * i[1] is used as a "true" com len, accounting for <><<>>
 */
static int	cmd_len(t_token *tokens, int *i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tokens[j].token && tokens[j].type != PIPE)
	{
		if (tokens[j].type == TOKEN)
		{
			if (!j || (j > 0 && tokens[j - 1].type != REDIR
					&& tokens[j - 1].type != HDOC))
				count++;
		}
		j += (tokens[j].type == REDIR || tokens[j].type == HDOC);
		if (!tokens[j].token)
			break ;
		j++;
	}
	if (count == 0)
		return (1);
	i[1] = count;
	i[4] = j;
	return (0);
}

static int	com_malloc_safe(t_data *data, int *i)
{
	data->coms[i[0]].com = malloc((i[1] + 1) * sizeof (char *));
	if (!data->coms[i[0]].com)
	{
		free_coms(data->coms);
		return (1);
	}
	return (0);
}

/*
 * 1. counts the commands using pipes, this count is done with cmd_count.
 * 2. allocs them.
 * 3. iteraties thru them (while ...).
 * 3.1. allocs the array of strings for each command (between pipes).
 *     the len of it is counted with cmd_len.
 * 3.2. fills each array with the commands, pasting the tokens.
 *     EXCEPT that is pastes io files into their own special arrays.
 *     for that, they're allocated first in io_coms_alloc, and then
 *     pasted into within com_filler func.
 */
int	cmd_loop(t_data *data, t_token *tokens)
{
	int	cmd_c;
	int	i[5];

	cmd_c = cmd_count(tokens);
	data->coms = malloc((cmd_c + 1) * sizeof (t_com));
	if (!data->coms)
		return (1);
	data->coms[cmd_c].com = NULL;
	i[0] = -1;
	i[3] = 0;
	while (++i[0] < cmd_c)
	{
		if (cmd_len(tokens + i[3], i))
			return (free_coms(data->coms), 1);
		if (com_malloc_safe(data, i))
			return (1);
		if (io_coms_alloc(&(data->coms[i[0]]), tokens + i[3], i[4]))
			return (free_coms(data->coms), 1);
		data->coms[i[0]].com[i[1]] = NULL;
		i[2] = -1;
		if (cmd_filler(data, i, tokens))
			return (free_coms(data->coms), 1);
		i[3] += i[2] + 1;
	}
	return (0);
}
