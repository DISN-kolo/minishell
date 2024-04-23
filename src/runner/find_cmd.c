/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:23:40 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/23 12:36:26 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	find_path(t_data *data, char **splited_path, int i, char **env)
{
	int		j;
	char	*path;

	j = 0;
	while (splited_path[j])
	{
		path = ft_strjoin3(splited_path[j], "/", data->coms[i].com[0]);
		if (!path)
			return (1);
		if (!access(path, F_OK))
			break ;
		free(path);
		j++;
	}
	if (splited_path[j])
	{
		free_double(splited_path);
		if (execve(path, data->coms[i].com, env) < 0)
			return (free(path), 0);
	}
	return (1);
}

static int	run_cmd(t_data *data, int i, char **env)
{
	char	*path;
	char	**splited_path;

	path = read_env(data, "PATH");
	if (path)
	{
		splited_path = ft_split(path, ':');
		if (!splited_path)
			return (1);
		if (find_path(data, splited_path, i, env))
			free_double(splited_path);
	}
	write(2, "Error: command not found\n", 25);
	return (1);
}

static int	run_absolute(t_data *data, int i, char **env)
{
	if (!access(data->coms[i].com[0], F_OK)
		&& execve(data->coms[i].com[0], data->coms[i].com, env))
		write(2, "Absolute path error on execve\n", 30);
	return (1);
}

static int	run_relative(t_data *data, int i, char **env)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	path = ft_strjoin3(pwd, "/", data->coms[i].com[0]);
	if (!path)
		return (1);
	if (!access(path, F_OK) && execve(path, data->coms[i].com, env))
		write(2, "Relative path error on execve\n", 30);
	return (1);
}

void	find_cmd(t_data *data, int i)
{
	char	**env;
	int		err;

	env = format_env(data);
	if (!env)
		exit(1);
	if (data->coms[i].com[0][0] == '/')
		err = run_absolute(data, i, env);
	else if (is_path(data->coms[i].com[0]))
		err = run_relative(data, i, env);
	else
		err = run_cmd(data, i, env);
	if (err)
		exit (1);
}
