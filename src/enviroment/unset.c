/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:13:41 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/28 12:59:26 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	remove_env(t_data *data, char *prop, int envi)
{
	char	**env;
	char	*key;
	int		i;
	int		j;

	env = malloc(ft_strslen(data->env[envi]) * sizeof (char *));
	if (!env)
		return (1);
	key = ft_strjoin(prop, "=");
	if (!key)
		return (free(env), 1);
	i = -1;
	j = 0;
	while (data->env[envi][++i])
	{
		if (ft_strncmp(key, data->env[envi][i], ft_strlen(key)))
			env[j++] = data->env[envi][i];
		else
			free(data->env[envi][i]);
	}
	free(key);
	free(data->env[envi]);
	env[j] = NULL;
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
		unset_env(data, keys[i], envi - 1);
		i++;
	}
	return (0);
}
