/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/05/10 14:11:20 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	token_recursive_loop(t_data *data, t_token *tokens)
{
	t_token	**token_list;
	int	i;

	token_list = create_tokens_list(tokens);
	if (!token_list)
		return (1);
	i = -1;
	while (token_list[++i])
	{
		if (token_list[i][0].type == AND || token_list[i][0].type == OR)
			continue ;
		if (run_cmds(data, token_list[i]))
			return (free_tokens_list(token_list), 1);
	}
	free_tokens_list(token_list);
	return (0);
}

int	token_loop(t_data *data)
{
	if (token_recursive_loop(data, data->tokens))
		return (MALLOC_ERR);
	if (dup2(data->std_out, 1) < 0 || dup2(data->std_in, 0) < 0)
		return (print_perror("Dup stdout and stdin", -1), 1);
	return (0);
}
