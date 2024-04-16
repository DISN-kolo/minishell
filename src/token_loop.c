/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/16 15:53:54 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		j += (tokens[j].type == REDIR);
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
static int	cmd_loop(t_data *data, t_token *tokens)
{
	int	cmd_c;
	int	i[5];

	cmd_c = cmd_count(tokens);
	printf("enterec cmd loop. counted cmds: %3d\n", cmd_c);
	data->coms = malloc((cmd_c + 1) * sizeof (t_com));
	if (!data->coms)
		return (1);
	data->coms[cmd_c].com = NULL;
	i[0] = -1;
	i[3] = 0;
	while (++i[0] < cmd_c)
	{
		cmd_len(tokens + i[3], i);
		printf("\tcounted cmd len of command #%3d: it is %3d\n\twith the TOTAL len being %3d\n", i[0], i[1], i[4]);
		data->coms[i[0]].com = malloc((i[1] + 1) * sizeof (char *));
		if (!data->coms[i[0]].com)
			return (free_coms(data), 1);
		if (io_coms_alloc(&(data->coms[i[0]]), tokens + i[3], i[4])) // TODO we need to allocate io arrays for a single command
			return (free_coms(data), 1);
		data->coms[i[0]].com[i[1]] = NULL;
		i[2] = -1;
		com_filler(data, i, tokens); // TODO
		printf("\ti[2] is %3d\n", i[2]);
		i[3] += i[2] + 1;
	}
	return (0);
}

int	token_loop(t_data *data)
{
	int		cmd_c;
	int		i;
	int		count;
	t_token	*current_tokens;

	i = -1;
	cmd_c = 0;
	while (data->tokens[++i].token) 
		cmd_c += !ft_strncmp(data->tokens[i].token, "||", 3)
			|| !ft_strncmp(data->tokens[i].token, "&&", 3);
	cmd_c++;
	i = 0;
	count = 0;
	while (i < cmd_c)
	{
		printf("i is %d\n", i);
		current_tokens = token_expander(data, data->tokens + count, &count);
		count++;
		printf("current tokens = great success! count (after ++) is %d\n", count);
		for (int x = 0; current_tokens[x].token; x++)
		{
			printf("\ttoken #%3d is '%s' with type %d\n", x, current_tokens[x].token, current_tokens[x].type);
		}
		cmd_loop(data, current_tokens);
		printf("command loop = great success!\n");
		printf("here's all the commands that we have thus far:\n");
		for (int x = 0; data->coms[x].com; x++)
		{
			printf("x = %3d\n", x);
			for (int j = 0; data->coms[x].com[j]; j++)
				printf("\tj = %3d, com[j] = %s\n", j, data->coms[x].com[j]);
		}
		printf("upon running:\n");
		run_cmds(data);
		printf("run cmds execd success\n");
		printf("\n");
		i++;
	}
	return (0);
}
