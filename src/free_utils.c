/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:10:50 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/28 16:12:26 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_double(char **p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
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

static int	free_env(t_data *data)
{
	char	***env;
	int		i;

	env = malloc(sizeof(char **) * 2);
	if (!env)
		return (1);
	env[1] = NULL;
	i = 0;
	while (data->env[i + 1])
		free_double(data->env[i++]);
	env[0] = data->env[i];
	free(data->env);
	data->env = env;
	return (0);
}

void	data_cleaner(t_data *data)
{
	int	i;

	if (data->env)
		free_env(data);
	data->env = 0;
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