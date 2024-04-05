/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:23:31 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/05 14:31:55 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*alloc_env(char **envp)
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
	env[len].value = NULL;
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

char	*read_env(t_data *data, char *key)
{
	int		i;

	i = 0;
	if (key[0] == '?')
		return (ft_itoa(data->status_code));
	while (data->env[i].key)
	{
		if (!ft_strncmp(key, data->env[i].key, ft_strlen(key) + 1))
			break ;
		i++;
	}
	if (data->env[i].key)
		return (data->env[i].value);
	return (NULL);
}

char	**format_env(t_data *data)
{
	char	**env;
	int		len;
	int		i;

	len = 0;
	while (data->env[len].key)
		len++;
	env = malloc((len + 1) * sizeof (char *));
	if (!env)
		return (NULL);
	i = 0;
	while (data->env[i].key)
	{
		env[i] = data->env[i].value;
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	find_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
