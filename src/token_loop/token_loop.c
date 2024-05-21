/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/05/21 13:36:53 by akozin           ###   ########.fr       */
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
	if (!open_error)
	{
		open_error = open_everything(data);
		if (!open_error)
		{
			run_cmds(data);
			if (dup2(data->std_out, 1) < 0 || dup2(data->std_in, 0) < 0)
				return (free_tokens(new_tokens), DUP2_ERR);
		}
		else if (open_error == -2 || open_error == -1)
			return (free_tokens(new_tokens), OPEN_ERR);
		else if (open_error == 1)
			return (free_tokens(new_tokens), NULL_ERR);
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
	data->coms_ind = 0;
	while (data->tokens_list[i])
	{
		if ((data->tokens_list[i][0].type == AND && g_err)
			|| (data->tokens_list[i][0].type == OR && !g_err))
			i++;
		else if (data->tokens_list[i][0].type != AND
			&& data->tokens_list[i][0].type != OR)
		{
			data->coms_ind = i/2;
			run_cmd(data, data->tokens_list[i]);
		}
		i++;
	}
	return (NULL_ERR);
}
