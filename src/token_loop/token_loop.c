/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/17 17:07:00 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		current_tokens = token_expander(data, data->tokens + count, &count);
		if (!current_tokens)
			return (1);
		count++;
		cmd_loop(data, current_tokens);
		run_cmds(data);
		i++;
	}
	return (0);
}
