/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/30 12:03:10 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_operators(t_data *data, int *count)
{
	printf("OP: %d\n", data->tokens[*count - 1].type);
	if ((data->tokens[*count - 1].type == AND && data->status_code)
		|| (data->tokens[*count - 1].type == OR && !data->status_code))
	{
		while (data->tokens[*count].token && !(data->tokens[*count].type == AND
				|| data->tokens[*count].type == OR))
			*count += 1;
		*count += 1;
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
	int		open_error;

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
		open_error = open_everything(data);
		if (!open_error)
			run_cmds(data);
		else if (open_error == -3)
			break ; // no command entered but there are redirs or something
		else
			printf("in token loop, open error = %d\n", open_error);
		for (int l = 0; data->coms[l].com; l++)
			printf("command %2d, fi: %2d, fo: %2d\n", l, data->coms[l].infd, data->coms[l].outfd);
		if (i + 1 < cmd_c && check_operators(data, &count))
			i++;
	}
	return (0);
}
