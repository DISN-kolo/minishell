/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:02:16 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/20 16:06:52 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*value_add_env(char *export, char *key)
{
	int		i;

	i = 0;
	while (export[i] && export[i] != '=')
		i++;
	if (export[i - 1] == '+')
		return (ft_substr(export, ft_strlen(key) + 2, ft_strlen(export)));
	else
		return (ft_substr(export, ft_strlen(key) + 1, ft_strlen(export)));
}

static t_env	*add_env(t_data *data, char *export, char *key)
{
	t_env	*env;
	int		len;
	int		i;

	len = 0;
	while (data->env[len].value)
		len++;
	env = malloc((len + 2) * sizeof (t_env));
	if (!env)
		return (free(key), NULL);
	i = -1;
	while (++i < len)
	{
		env[i].key = data->env[i].key;
		env[i].value = data->env[i].value;
		env[i].exp = data->env[i].exp;
	}
	env[i].key = key;
	env[i].value = value_add_env(export, key);
	if (!env[i].value)
		return (free_env(env), NULL);
	env[i].exp = find_equal(export);
	env[i + 1].key = NULL;
	env[i + 1].value = NULL;
	return (free(data->env), env);
}

static char	*value_update_env(t_data *data, char *export, char *key)
{
	char	*app;
	char	*value;
	int		i;

	i = 0;
	while (export[i] && export[i] != '=')
		i++;
	if (export[i - 1] == '+')
	{
		app = ft_substr(export, ft_strlen(key) + 2, ft_strlen(export));
		if (!app)
			return (NULL);
		value = ft_strjoin(read_env(data, key), app);
		free(app);
		return (value);
	}
	else
		return (ft_substr(export, ft_strlen(key) + 1, ft_strlen(export)));
}

static int	update_env(t_data *data, char *export, char	*key)
{
	int	i;

	i = 0;
	while (data->env[i].key)
	{
		if (!ft_strncmp(key, data->env[i].key, ft_strlen(key) + 1))
			break ;
		i++;
	}
	free(data->env[i].value);
	data->env[i].value = value_update_env(data, export, key);
	if (!data->env[i].value)
		return (1);
	return (0);
}

int	export_env(t_data *data, char *export)
{
	char	*key;
	int		key_len;

	if (!(ft_isalpha(export[0]) || export[0] == '_'))
		return (1);
	key_len = 0;
	while (export[key_len] && export[key_len] != '=' && export[key_len] != '+')
		key_len++;
	key = ft_substr(export, 0, key_len);
	if (!key)
		return (1);
	if (read_env(data, key))
	{
		if (update_env(data, export, key))
			return (free(key), 1);
		free(key);
	}
	else
	{
		data->env = add_env(data, export, key);
		if (!data->env)
			return (1);
	}
	return (0);
}
