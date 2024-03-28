/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:44:55 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/28 12:42:33 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_env(char **env) //TODO repeated funciton (create free_utils.c)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}

static char	**alloc_env(char **envp)
{
	char	**env;
	int		len;
	int		i;

	len = ft_strslen(envp);
	env = malloc((len + 1) * sizeof (char *));
	if (!env)
		return (NULL);
	env[len] = NULL;
	i = 0;
	while (i < len)
	{
		env[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		if (!env[i])
			return (free_env(env), NULL);
		i++;
	}
	return (env);
}

char	***create_env(char **envp)
{
	char	***env;

	env = malloc(sizeof (char **) * 2);
	if (!env)
		return (NULL);
	env[0] = alloc_env(envp);
	if (!env[0])
		return (free(env), NULL);
	env[1] = NULL;
	return (env);
}

int	dup_env(t_data *data)
{
	char	***env;
	char	**new_env;
	int		len;
	int		i;

	len = 0;
	while (data->env[len])
		len++;
	env = malloc((len + 2) * sizeof (char ***));
	if (!env)
		return (1);
	new_env = alloc_env(data->env[len - 1]);
	if (!new_env)
		return (free(env), 1);
	i = -1;
	while (++i < len)
		env[i] = data->env[i];
	env[i] = new_env;
	env[i + 1] = NULL;
	free(data->env);
	data->env = env;
	return (0);
}
