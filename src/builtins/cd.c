/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:29:33 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/03 15:53:02 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	update_pwd(t_data *data, char *path)
{
	char	*pwd;

	pwd = ft_strjoin("PWD=", path);
	if (!pwd)
		return (1);
	if (export_env(data, pwd))
		return (1);
	free(pwd);
	return (0);
}

static void	update_path(t_data *data, char *path, char *arg)
{
	if (chdir(path) < 0)
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
	}
	else
		update_pwd(data, path);
}

void	bcd(t_data *data, char **args)
{
	char	*dir;
	char	*path;

	if (!args[0])
		update_path(data, read_env(data, "HOME"), NULL);
	else if (args[0][0] == '/')
		update_path(data, args[0], args[0]);
	else
	{
		dir = ft_strjoin(read_env(data, "PWD"), "/");
		if (!dir)
			return ;
		path = ft_strjoin(dir, args[0]);
		if (!path)
			return ;
		update_path(data, path, args[0]);
		free(dir);
		free(path);
	}
}
