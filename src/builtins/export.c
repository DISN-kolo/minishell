/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:09:48 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/03 15:15:27 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	data->env[i].value = ft_substr(export, ft_strlen(key) + 1,
			ft_strlen(export));
	if (!data->env[i].value)
		return (1);
	return (0);
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
	env[i].value = ft_substr(export, ft_strlen(key) + 1, ft_strlen(export));
	if (!env[i].value)
		return (free_env(env), NULL);
	env[i].exp = find_equal(export);
	env[i + 1].key = NULL;
	return (free(data->env), env);
}

int	export_env(t_data *data, char *export)
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

static int	print_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i].key)
	{
		if (data->env[i].exp)
			printf("declare -x %s=\"%s\"\n",
				data->env[i].key, data->env[i].value);
		else
			printf("declare -x %s\n", data->env[i].key);
		i++;
	}
	return (0);
}

int	bexport(t_data *data, char **exports)
{
	int	i;

	if (!exports)
		return (print_export(data));
	i = 0;
	while (exports[i])
	{
		if (export_env(data, exports[i]))
			write(2, "Export params error\n", 20);
		i++;
	}
	return (0);
}
