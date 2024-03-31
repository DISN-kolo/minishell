/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:09:48 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/31 13:55:33 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	update_env(t_data *data, char *export, char	*key, int envi)
{
	int	i;

	i = 0;
	while (data->env[envi][i].key)
	{
		if (!ft_strncmp(key, data->env[envi][i].key, ft_strlen(key) + 1))
			break ;
		i++;
	}
	free(data->env[envi][i].value);
	data->env[envi][i].value = ft_substr(export, ft_strlen(key) + 1,
			ft_strlen(export));
	if (!data->env[envi][i].value)
		return (1);
	return (0);
}

static t_env	*add_env(t_data *data, char *export, char *key, int envi)
{
	t_env	*env;
	int		len;
	int		i;

	len = 0;
	while (data->env[envi][len].value)
		len++;
	env = malloc((len + 2) * sizeof (t_env));
	if (!env)
		return (free(key), NULL);
	i = -1;
	while (++i < len)
	{
		env[i].key = data->env[envi][i].key;
		env[i].value = data->env[envi][i].value;
		env[i].exp = data->env[envi][i].exp;
	}
	env[i].key = key;
	env[i].value = ft_substr(export, ft_strlen(key) + 1, ft_strlen(export));
	if (!env[i].value)
		return (free_env(env), NULL);
	env[i].exp = find_equal(export);
	env[i + 1].key = NULL;
	return (free(data->env[envi]), env);
}

static int	export_env(t_data *data, char *export, int envi)
{
	char	*key;
	int		key_len;

	if (!(ft_isalpha(export[0]) || export[0] == '_'))
		return (1);
	key_len = 0;
	while (export[key_len] && export[key_len] != '=')
		key_len++;
	key = ft_substr(export, 0, key_len);
	if (!key)
		return (1);
	if (read_env(data, key, envi))
	{
		if (update_env(data, export, key, envi))
			return (free(key), 1);
		free(key);
	}
	else
	{
		data->env[envi] = add_env(data, export, key, envi);
		if (!data->env[envi])
			return (1);
	}
	return (0);
}

static void	print_export(t_data *data, int envi)
{
	int	i;

	i = 0;
	while (data->env[envi][i].key)
	{
		if (data->env[envi][i].exp)
			printf("declare -x %s=\"%s\"\n",
				data->env[envi][i].key, data->env[envi][i].value);
		else
			printf("declare -x %s\n", data->env[envi][i].key);
		i++;
	}
}

int	bexport(t_data *data, char **exports)
{
	int	envi;
	int	i;

	if (dup_env(data))
		return (1);
	envi = 0;
	while (data->env[envi])
		envi++;
	if (!exports)
	{
		print_export(data, envi - 1);
		return (0);
	}
	i = 0;
	while (exports[i])
	{
		if (export_env(data, exports[i], envi - 1))
			write(2, "Export params error\n", 20);
		i++;
	}
	return (0);
}
