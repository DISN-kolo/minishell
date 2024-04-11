/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/11 15:51:27 by akozin           ###   ########.fr       */
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
		if (tokens[i].is_pipe)
			count++;
		i++;
	}
	return (count);
}

static int	cmd_len(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token && !tokens[i].is_pipe)
		i++;
	return (i);
}

static int	cmd_loop(t_data *data, t_token *tokens)
{
	int	cmd_c;
	int	i[4];

	cmd_c = cmd_count(tokens);
	data->coms = malloc((cmd_c + 1) * sizeof (t_com));
	if (!data->coms)
		return (1);
	data->coms[cmd_c].com = NULL;
	i[0] = -1;
	i[3] = 0;
	while (++i[0] < cmd_c)
	{
		i[1] = cmd_len(tokens + i[3]);
		data->coms[i[0]].com = malloc((i[1] + 1) * sizeof (char *));
		if (!data->coms[i[0]].com)
			return (free_coms(data), 1);
		if (io_coms_alloc(&(data->coms[i[0]]), tokens +)) // TODO we need to allocate io arrays for a single command
			return (free_coms(data), 1);
		data->coms[i[0]].com[i[1]] = NULL;
		i[2] = -1;
		com_filler(data, i); // TODO
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
		cmd_loop(data, current_tokens);
		printf("command loop = great success!\n");
		printf("here's all the commands that we have thus far:\n");
		for (int x = 0; data->coms[x].com; x++)
		{
			printf("x = %3d\n", x);
			for (int j = 0; data->coms[x].com[j]; j++)
				printf("\tj = %3d, com[j] = %s\n", j, data->coms[x].com[j]);
		}
		run_cmds(data);
		i++;
	}
	return (0);
}
