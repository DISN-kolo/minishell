/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/16 16:57:49 by akozin           ###   ########.fr       */
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
		printf("i is %3d\n", i);
		current_tokens = token_expander(data, data->tokens + count, &count);
		count++;
		cmd_loop(data, current_tokens);
		printf("here's all the commands that we have thus far:\n");
		for (int x = 0; data->coms[x].com; x++)
		{
			printf("x = %3d\n", x);
			for (int j = 0; data->coms[x].com[j]; j++)
				printf("\tj = %3d,  com[j] = %s\n", j, data->coms[x].com[j]);
			printf("ins:\n");
			for (int jj = 0; data->coms[x].ins[jj].fname; jj++)
				printf("\tj = %3d,  ins[j] = %s, double = %s\n", jj, data->coms[x].ins[jj].fname, data->coms[x].ins[jj].dub ? "true" : "false");
			printf("outs:\n");
			for (int jjj = 0; data->coms[x].outs[jjj].fname; jjj++)
				printf("\tj = %3d, outs[j] = %s, double = %s\n", jjj, data->coms[x].outs[jjj].fname, data->coms[x].outs[jjj].dub ? "true" : "false");
		}
		run_cmds(data);
		printf("\n========block %3d ended.\n", i);
		i++;
	}
	return (0);
}
