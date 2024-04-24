/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/24 16:20:20 by akozin           ###   ########.fr       */
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
		printf("amb redir on: %i with token: '%s'\n", data->amb_redir_ind, data->tokens[data->amb_redir_ind].token);
		for (int x = 0; data->tokens[x].token; x++)
		{
			printf("i = %2d, x = %2d, token = '%s'\n", i, x, data->tokens[x].token);
		}
		if (!current_tokens)
			return (1);
		count++;
		cmd_loop(data, current_tokens);
		for (int x = 0; data->coms[x].com; x++)
		{
			for (int y = 0; data->coms[x].ios[y].fname; y++)
				printf("i = %2d, x = %2d, y = %2d, io = '%s'\n", i, x, y, data->coms[x].ios[y].fname);
		}
		open_error = open_everything(data);
		if (open_error != -2 && open_error != -1)
			run_cmds(data);
		i++;
	}
	return (0);
}
