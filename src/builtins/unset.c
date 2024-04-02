/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:13:41 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/31 13:55:33 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	copy_remove_env(t_data *data, int envi, char *key, t_env *env)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (data->env[envi][++i].key)
	{
		if (ft_strncmp(key, data->env[envi][i].key, ft_strlen(key) + 1))
		{
			env[j].key = data->env[envi][i].key;
			env[j].value = data->env[envi][i].value;
			env[j++].exp = data->env[envi][i].exp;
		}
		else
		{
			free(data->env[envi][i].key);
			free(data->env[envi][i].value);
		}
	}
	env[j].key = NULL;
}

static int	remove_env(t_data *data, char *key, int envi)
{
	t_env	*env;
	int		len;

	len = 0;
	while (data->env[envi][len].key)
		len++;
	env = malloc(len * sizeof (t_env));
	if (!env)
		return (1);
	copy_remove_env(data, envi, key, env);
	free(data->env[envi]);
	data->env[envi] = env;
	return (0);
}

static int	unset_env(t_data *data, char *key, int envi)
{
	if (!(ft_isalpha(key[0]) || key[0] == '_') || ft_strchr(key, '='))
		return (1);
	if (read_env(data, key, envi))
	{
		if (remove_env(data, key, envi))
			return (1);
	}
	return (0);
}

int	bunset(t_data *data, char **keys)
{
	int	envi;
	int	i;

	if (dup_env(data))
		return (1);
	envi = 0;
	while (data->env[envi])
		envi++;
	i = 0;
	while (keys[i])
	{
		if (unset_env(data, keys[i], envi - 1))
			write(2, "Unset params error\n", 19);
		i++;
	}
	return (0);
}
