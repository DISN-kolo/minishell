/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:23:31 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/31 12:48:04 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*read_env(t_data *data, char *key, int envi)
{
	int		i;

	i = 0;
	while (data->env[envi][i].key)
	{
		if (!ft_strncmp(key, data->env[envi][i].key, ft_strlen(key) + 1))
			break ;
		i++;
	}
	if (data->env[envi][i].key)
		return (data->env[envi][i].value);
	return (NULL);
}

char	**format_env(t_env *env)
{
	char	**new_env;
	int		len;
	int		i;

	len = 0;
	while (env[len].value)
		len++;
	new_env = malloc((len + 1) * sizeof (char *));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i].value)
		new_env[i] = env[i].value;
	new_env[i] = NULL;
	return (new_env);
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
