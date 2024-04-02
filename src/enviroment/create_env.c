/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:44:55 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/31 12:35:56 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env	*alloc_env(char **envp)
{
	t_env	*env;
	int		len;
	int		i;
	int		j;

	len = ft_strslen(envp);
	env = malloc((len + 1) * sizeof (t_env));
	if (!env)
		return (NULL);
	env[len].key = NULL;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		env[i].key = ft_substr(envp[i], 0, j);
		env[i].value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
		if (!env[i].key || !env[i].value)
			return (free_env(env), NULL);
		env[i].exp = 1;
		i++;
	}
	return (env);
}

t_env	**create_env(char **envp)
{
	t_env	**env;

	env = malloc(sizeof (t_env *) * 2);
	if (!env)
		return (NULL);
	env[0] = alloc_env(envp);
	if (!env[0])
		return (free(env), NULL);
	env[1] = NULL;
	return (env);
}

static t_env	*create_dup_env(t_data *data, int envi)
{
	t_env	*new_env;
	int		i;

	i = 0;
	while (data->env[envi][i].key)
		i++;
	new_env = malloc((i + 1) * sizeof(t_env));
	if (!new_env)
		return (NULL);
	i = -1;
	while (data->env[envi][++i].key)
	{
		new_env[i].key = ft_substr(data->env[envi][i].key, 0,
				ft_strlen(data->env[envi][i].key));
		if (!new_env[i].key)
			return (free(new_env), NULL);
		new_env[i].value = ft_substr(data->env[envi][i].value, 0,
				ft_strlen(data->env[envi][i].value));
		if (!new_env[i].value)
			return (free(new_env), free(new_env[i].key), NULL);
		new_env[i].exp = data->env[envi][i].exp;
	}
	new_env[i].key = NULL;
	return (new_env);
}

int	dup_env(t_data *data)
{
	t_env	**env;
	t_env	*new_env;
	int		len;
	int		i;

	len = 0;
	while (data->env[len])
		len++;
	env = malloc((len + 2) * sizeof (t_env *));
	if (!env)
		return (1);
	new_env = create_dup_env(data, len - 1);
	if (!new_env)
		return (free(env), 1);
	i = -1;
	while (++i < len)
		env[i] = data->env[i];
	env[i] = new_env;
	env[i + 1] = NULL;
	free(data->env);
	data->env = env;
	return (0);
}
