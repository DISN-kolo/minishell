/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/05/20 13:11:41 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/errors.h"

static t_error	run_cmd(t_data *data, t_token *tokens)
{
	t_token	*new_tokens;
	int		open_error;

	new_tokens = token_expander(data, tokens);
	if (!new_tokens)
		return (MALLOC_ERR);
	open_error = cmd_loop(data, new_tokens);
	printf("in run cmd, open error = %d\n", open_error);
	if (!open_error)
	{
		printf("wow no 1st open error!!\n");
		open_error = open_everything(data);
		if (!open_error)
		{
			run_cmds(data);
			if (dup2(data->std_out, 1) < 0 || dup2(data->std_in, 0) < 0)
				return (printf("EPIC FAIL ON DUP2!!!\n"), free_tokens(new_tokens), DUP2_ERR);
		}
		else if (open_error == -2 || open_error == -1)
			return (printf("EPIC FAIL ON OPEN ERROR: %d\n", open_error), free_tokens(new_tokens), OPEN_ERR);
		else if (open_error == 1)
			return (printf("ERROR 1\n"), free_tokens(new_tokens), NULL_ERR);
	}
	free_tokens(new_tokens);
	if (open_error == 1)
		return (MALLOC_ERR);
	return (NULL_ERR);
}

t_error	token_loop(t_data *data)
{
	int	i;

	data->tokens_list = create_tokens_list(data->tokens);
	if (!data->tokens_list)
		return (MALLOC_ERR);
	i = 0;
	for (int x = 0; data->tokens_list[x]; x++)
	{
		for (int y = 0; data->tokens_list[x][y].token; y++)
			printf("[%2d][%2d] '%s'\n", x, y, data->tokens_list[x][y].token);
		printf("\n");
	}
	while (data->tokens_list[i])
	{
		if ((data->tokens_list[i][0].type == AND && g_err)
			|| (data->tokens_list[i][0].type == OR && !g_err))
			i++;
		else if (data->tokens_list[i][0].type != AND
			&& data->tokens_list[i][0].type != OR)
			run_cmd(data, data->tokens_list[i]);
		i++;
	}
	return (NULL_ERR);
}
