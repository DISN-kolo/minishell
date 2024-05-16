/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:16:17 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/16 19:16:38 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	data_cleaner(t_data *data)
{
	free_tokens(data->tokens);
	data->tokens = NULL;
	free_token_list(data->tokens_list);
	data->tokens_list = NULL;
	free_heredocs(data->hds);
	data->hds = NULL;
	data->hd_counter = 0;
	data->local_status = 0;
	data->sp_hdoc = -1;
}

void	free_env(t_env *env)
{
	int	i;

	if (!env)
		return ;
	i = -1;
	while (env[++i].key && env[i].value)
	{
		if (env[i].key)
			free(env[i].key);
		if (env[i].value)
			free(env[i].value);
	}
	free(env);
}
