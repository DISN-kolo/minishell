/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:14:33 by akozin            #+#    #+#             */
/*   Updated: 2024/04/17 15:30:50 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cmd_count(t_token *tokens)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (tokens[i].token && ft_strncmp(tokens[i].token, "||", 3)
		&& ft_strncmp(tokens[i].token, "&&", 3))
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
static void	cmd_len(t_token *tokens, int *i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tokens[j].token && tokens[j].type != PIPE)
	{
		count += (tokens[j].type == TOKEN);
		j += (tokens[j].type == REDIR || tokens[j].type == HDOC);
		j++;
	}
	i[1] = count;
	i[4] = j;
}

/*
 * 1. counts the commands until || or && using pipes.
 *   this count is done with cmd_count.
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
		cmd_len(tokens + i[3], i);
		data->coms[i[0]].com = malloc((i[1] + 1) * sizeof (char *));
		if (!data->coms[i[0]].com)
			return (free_coms(data), 1);
		if (io_coms_alloc(&(data->coms[i[0]]), tokens + i[3], i[4]))
			return (free_coms(data), 1);
		data->coms[i[0]].com[i[1]] = NULL;
		i[2] = -1;
		cmd_filler(data, i, tokens);
		printf("\ti[2] is %3d\n", i[2]);
		i[3] += i[2] + 1;
	}
	return (0);
}

