/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:09:48 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/28 12:43:20 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	update_env(t_data *data, char *export, char	*key, int envi)
{
	int	i;

	i = 0;
	while (data->env[envi][i])
	{
		if (!ft_strncmp(key, data->env[envi][i], ft_strlen(key)))
			break ;
	}
	free(data->env[envi][i]);
	data->env[envi][i] = ft_substr(export, 0, ft_strlen(export));
	if (!data->env[envi][i])
		return (1);
	return (0);
}

static int	add_env(t_data *data, char *export, int envi)
{
	char	**env;
	int		len;
	int		i;

	len = ft_strslen(data->env[envi]);
	env = malloc((len + 2) * sizeof (char *));
	if (!env)
		return (1);
	i = -1;
	while (++i < len)
		env[i] = data->env[envi][i];
	env[i] = ft_substr(export, 0, ft_strlen(export));
	if (!env[i])
		return (free_double(env), 1);
	env[i + 1] = NULL;
	free(data->env[envi][i]);
	data->env[envi] = env;
	return (0);
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
	}
	else
	{
		if (add_env(data, export, envi))
			return (free(key), 1);
	}
	free(key);
	return (0);
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
	i = 0;
	while (exports[i])
	{
		if (export_env(data, exports[i], envi - 1))
			write(2, "Export params error\n", 20);
		i++;
	}
	return (0);
}
