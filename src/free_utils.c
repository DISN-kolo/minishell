/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:10:50 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/05 14:35:02 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_double(char **p)
{
	int	i;

	if (!p)
		return ;
	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

int	free_ret(t_token **ret)
{
	int	i;

	i = 0;
	while ((*ret)[i].token)
	{
		free((*ret)[i].token);
		// TODO
//		if ((*ret)[i].literal)
//		{
//			free((*ret)[i].literal);
//			(*ret)[i].literal = NULL;
//		}
		(*ret)[i].token = NULL;
		i++;
	}
	free(*ret);
	return (1);
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

void	data_cleaner(t_data *data)
{
	int	i;

	if (data->tokens)
		free_ret(&data->tokens);
	data->tokens = 0;
	i = 0;
	if (data->coms)
	{
		while (data->coms[i].oper)
		{
			free_double(data->coms[i].com);
			i++;
		}
		free(data->coms);
	}
	data->coms = 0;
	data->errored = 0;
}
