/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:59:19 by akozin            #+#    #+#             */
/*   Updated: 2024/04/08 13:19:04 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	prepare_commands(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->tokens[i].token)
	{
		if (ft_strncmp(data->tokens[i].token, "&&", 3)
				|| ft_strncmp(data->tokens[i].token, "||", 3))
			count++;
		i++;
	}
	data->coms = malloc(sizeof (t_com) * (count + 2));
	if (data->coms)
		data->coms[count + 1].com = NULL;
}

void	token_loop(t_data *data)
{
	int		i;
	int		k;
	t_token	*current_tokens;

	prepare_commands(data);
	current_tokens = NULL;
	if (!data->coms)
		return ; // TODO err handling
	i = 0;
	k = 0;
	while (data->coms[k].com)
	{
		while (!ft_strncmp(data->tokens[i].token, "&&", 3)
				&& !ft_strncmp(data->tokens[i].token, "||", 3))
		{
			current_tokens = tokens_join_free(current_tokens, &(data->tokens[i]));
			i++;
		}
		token_expander(data, current_tokens);
//		command_fill(&(data->coms[k]), current_tokens); // TODO
		k++;
	}
}
