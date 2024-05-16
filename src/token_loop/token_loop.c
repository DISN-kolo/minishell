/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/05/16 12:45:49 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/errors.h"

int	run_cmd(t_data *data, t_token *tokens)
{
	t_token	*new_tokens;
	int		open_error;

	new_tokens = token_expander(data, tokens);
	if (!new_tokens)
		return (1);
	cmd_loop(data, new_tokens);
	open_error = open_everything(data);
	if (!open_error)
	{
		run_cmds(data);
		if (dup2(data->std_out, 1) < 0 || dup2(data->std_in, 0) < 0)
			return (print_perror("Dup stdout and stdin", -1), 1);
	}
	else if (open_error == -3)
		return (1); // no command entered but there are redirs or something
	else
		printf("in token loop, open error = %d\n", open_error);
	free_coms(data->coms);
	return (0);
}

int	token_loop(t_data *data)
{
	int	i;

	data->tokens_list = create_tokens_list(data->tokens);
	if (!data->tokens_list)
		return (MALLOC_ERR);
	i = 0;
	while (data->tokens_list[i])
	{
		if ((data->tokens_list[i][0].type == AND && g_err) || (data->tokens_list[i][0].type == OR && !g_err))
			i++;
		else if (data->tokens_list[i][0].type == TOKEN) 
			run_cmd(data, data->tokens_list[i]);
		i++;
	}
	return (0);
}
