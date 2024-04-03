/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:13:41 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/03 15:09:03 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	copy_remove_env(t_data *data, char *key, t_env *env)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (data->env[++i].key)
	{
		if (ft_strncmp(key, data->env[i].key, ft_strlen(key) + 1))
		{
			env[j].key = data->env[i].key;
			env[j].value = data->env[i].value;
			env[j++].exp = data->env[i].exp;
		}
		else
		{
			free(data->env[i].key);
			free(data->env[i].value);
		}
	}
	env[j].key = NULL;
}

static int	remove_env(t_data *data, char *key)
{
	t_env	*env;
	int		len;

	len = 0;
	while (data->env[len].key)
		len++;
	env = malloc(len * sizeof (t_env));
	if (!env)
		return (1);
	copy_remove_env(data, key, env);
	free(data->env);
	data->env = env;
	return (0);
}

static int	unset_env(t_data *data, char *key)
{
	if (!(ft_isalpha(key[0]) || key[0] == '_') || ft_strchr(key, '='))
		return (1);
	if (read_env(data, key))
	{
		if (remove_env(data, key))
			return (1);
	}
	return (0);
}

int	bunset(t_data *data, char **keys)
{
	int	i;

	i = 0;
	while (keys[i])
	{
		if (unset_env(data, keys[i]))
			write(2, "Unset params error\n", 19);
		i++;
	}
	return (0);
}
