/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:13:41 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/30 13:44:22 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	copy_remove_env(t_data *data, int envi, char *key, t_env *env)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (data->env[envi][++i].value)
	{
		if (ft_strncmp(key, data->env[envi][i].value, ft_strlen(key)))
			env[j++].value = data->env[envi][i].value;
		else
			free(data->env[envi][i].value);
	}
	env[j].value = NULL;
}

static int	remove_env(t_data *data, char *prop, int envi)
{
	t_env	*env;
	char	*key;
	int		len;

	len = 0;
	while (data->env[envi][len].value)
		len++;
	env = malloc((len + 1) * sizeof (t_env));
	if (!env)
		return (1);
	key = ft_strjoin(prop, "=");
	if (!key)
		return (free(env), 1);
	copy_remove_env(data, envi, key, env);
	free(key);
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
		unset_env(data, keys[i], envi - 1);
		i++;
	}
	return (0);
}
