/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:10:50 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/01 17:03:22 by akozin           ###   ########.fr       */
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
	{
		free(p[i]);
		p[i++] = NULL;
	}
	free(p);
	p = NULL;
}

int	free_ret(t_token **ret)
{
	int	i;

	i = 0;
	if (!*ret)
		return (0);
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
	*ret = NULL;
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
		while (data->coms[i].com)
		{
			if (data->coms[i].infd != -42 && close(data->coms[i].infd) < 0)
				print_perror("Close infd data cleaner", -1);
			if (data->coms[i].outfd != -42 && close(data->coms[i].outfd) < 0)
				print_perror("Close outfd data cleaner", -1);
			free_double(data->coms[i].com);
			data->coms[i].com = NULL;
			i++;
		}
		free(data->coms);
	}
	data->coms = NULL;
	data->errored = 0;
}

void	free_coms(t_data *data)
{
	int	i;

	if (!data->coms)
		return ;
	i = 0;
	while (data->coms[i].com)
	{
		free_double(data->coms[i].com);
		i++;
	}
	free(data->coms);
	data->coms = NULL;
}
