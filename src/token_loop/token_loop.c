/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/25 15:48:03 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	token_loop(t_data *data)
{
	int		cmd_c;
	int		i;
	int		count;
	t_token	*current_tokens;
	int		open_error;

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
		current_tokens = token_expander(data, data->tokens + count, &count);
		if (data->amb_tok_ind != -42)
			printf("amb tok on: %i with token: '%s'\n", data->amb_tok_ind, data->tokens[data->amb_tok_ind].token);
		if (!current_tokens)
			return (1);
		count++;
		cmd_loop(data, current_tokens);
		open_error = open_everything(data);
		if (!open_error)
			run_cmds(data);
		else
			printf("open error = %d\n", open_error);
		i++;
	}
	return (0);
}
