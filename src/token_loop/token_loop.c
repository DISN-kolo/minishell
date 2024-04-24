/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/23 20:55:09 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_operators(t_data *data, int *count)
{
	if ((data->tokens[*count - 1].token[0] == '&' && data->status_code)
		|| (data->tokens[*count - 1].token[0] == '|' && !data->status_code))
	{
		while (data->tokens[*count].token
			&& !(data->tokens[*count].token[0] == '&'
			|| data->tokens[*count].token[0] == '|'))
			*count += 1;
		*count += 1;
		printf("A: %s\n", data->tokens[*count].token);
		return (1);
	}
	return (0);
}

int	token_loop(t_data *data)
{
	t_token	*current_tokens;
	int		cmd_c;
	int		i;
	int		count;

	i = -1;
	cmd_c = 0;
	while (data->tokens[++i].token)
		cmd_c += !ft_strncmp(data->tokens[i].token, "||", 3)
			|| !ft_strncmp(data->tokens[i].token, "&&", 3);
	cmd_c++;
	i = -1;
	count = 0;
	while (++i < cmd_c)
	{
		current_tokens = token_expander(data, data->tokens + count, &count);
		if (!current_tokens)
			return (1);
		count++;
		cmd_loop(data, current_tokens);
		run_cmds(data);
		if (i + 1 < cmd_c && check_operators(data, &count))
			i++;
	}
	return (0);
}
