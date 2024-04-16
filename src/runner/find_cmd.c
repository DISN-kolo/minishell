/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:23:40 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/16 13:10:11 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	run_cmd(t_data *data, int i) //TODO control errors!!!!!!
{
	char	*path;
	char	**splited_path;
	int		j;

	path = read_env(data, "PATH");
	if (path)
	{
		splited_path = ft_split(path, ':');
		if (!splited_path)
			return (1);
		j = -1;
		while (splited_path[++j])
		{
			path = ft_strjoin3(splited_path[j], "/", data->coms[i].com[0]);
			if (!path)
				return (free_double(splited_path), 1);
			if (!access(path, F_OK))
				break ;
			free(path);
		}
		if (splited_path[j])
		{
			free_double(splited_path);
			if (execve(path, data->coms[i].com, NULL) < 0)
				return (free(path) , 1);
		}
	}
	write(2, "Error: command not found\n", 25);
	return (0);
}

static void	run_absolute(t_data *data, int i)
{
	if (!access(data->coms[i].com[0], F_OK)
			&& execve(data->coms[i].com[0], data->coms[i].com, NULL))
		write(2, "Absolute path error on execve\n", 30);
}

static void	run_relative(t_data *data, int i)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	path = ft_strjoin3(pwd, "/", data->coms[i].com[0]);
	if (!path)
		return ;
	if (!access(path, F_OK)
			&& execve(path, data->coms[i].com, NULL))
		write(2, "Relative path error on execve\n", 30);
}

static int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	find_cmd(t_data *data, int i)
{
	if (data->coms[i].com[0][0] == '/')
		run_absolute(data, i);
	else if (is_path(data->coms[i].com[0]))
		run_relative(data, i);
	else
		run_cmd(data, i);
}
