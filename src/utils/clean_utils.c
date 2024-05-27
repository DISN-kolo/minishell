/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:16:17 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/23 11:37:57 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	delete_if_latest_hd(t_data *data, int *i)
{
	char	*fname;

	if (data->hds[i[0]][i[1]].latest)
	{
		fname = gen_h_fname(data, i);
		if (!fname)
			return (1);
		unlink(fname);
		if (data->hds[i[0]][i[1]].expand)
		{
			fname = ft_strjoin_free(fname, "_exp");
			if (!fname)
				return (1);
			unlink(fname);
		}
		free(fname);
	}
	return (0);
}

static void	unlink_hds(t_data *data)
{
	int		i[2];

	if (!data->hds)
		return ;
	i[0] = 0;
	while (data->hds[i[0]])
	{
		i[1] = 0;
		while (data->hds[i[0]][i[1]].str)
		{
			if (delete_if_latest_hd(data, i))
				return ;
			i[1]++;
		}
		i[0]++;
	}
}

void	data_cleaner(t_data *data)
{
	free_tokens(data->tokens);
	data->tokens = NULL;
	free_token_list(data->tokens_list);
	data->tokens_list = NULL;
	unlink_hds(data);
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
