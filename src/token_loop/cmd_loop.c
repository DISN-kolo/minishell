/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:14:33 by akozin            #+#    #+#             */
/*   Updated: 2024/05/20 13:09:26 by akozin           ###   ########.fr       */
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
	printf("inside cmd len\n");
	for (int x = 0; tokens[x].token; x++)
		printf("\t'%s'\n", tokens[x].token);
	j += tokens[0].type == PIPE;
	i[2] += tokens[0].type == PIPE;
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
	printf("cmd_c = %d\n", cmd_c);
	data->coms = malloc((cmd_c + 1) * sizeof (t_com));
	if (!data->coms)
		return (printf("malloc error in cmd loop??????\n"), 1);
	data->coms[cmd_c].com = NULL;
	i[0] = -1;
	i[3] = 0;
	while (++i[0] < cmd_c)
	{
		printf("inside cmd loop i[0] is %2d\n", i[0]);
		if (cmd_len(tokens + i[3], i))
			return (printf("cmdlen if\n"), free(data->coms), 0);
		if (com_malloc_safe(data, i))
			return (printf("cmdmalloc if\n"), 1);
		if (io_coms_alloc(&(data->coms[i[0]]), tokens + i[3], i[4]))
			return (printf("io comms alloc if\n"), free_coms(data->coms), 1);
		data->coms[i[0]].com[i[1]] = NULL;
		i[2] = -1;
		if (cmd_filler(data, i, tokens))
			return printf("cmdfill if\n"), (free_coms(data->coms), 1);
		i[3] += i[2] + 1;
	}
	return (printf("wooo exit 0 cmd loop\n"), 0);
}
