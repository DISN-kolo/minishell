/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/16 16:15:33 by akozin           ###   ########.fr       */
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
