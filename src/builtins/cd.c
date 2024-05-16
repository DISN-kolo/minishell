/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:29:33 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/16 16:21:38 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	export_pwd(t_data *data, char *key, char *value)
{
	char	*export;

	export = ft_strjoin3(key, "=", value);
	if (!export)
		return (1);
	if (export_env(data, export))
		return (free(export), 1);
	free(export);
	return (0);
}

static int	update_path(t_data *data, char *path)
{
	char	*pwd;

	if (chdir(path) < 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		return (1);
	}
	else
	{
		pwd = read_env(data, "PWD");
		if (!pwd)
			return (1);
		if (export_pwd(data, "OLDPWD", pwd))
			return  (free(pwd), 1);
		free(pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		if (export_pwd(data, "PWD", pwd))
			return (free(pwd), 1);
		free(pwd);
		return (0);
	}
}

static int	cd_home(t_data *data)
{
	char	*home;

	home = read_env(data, "HOME");
	if (home)
	{
		if (update_path(data, home))
			return (free(home), 1);
		free(home);
	}
	else
		return (print_error(NULL, "cd", "HOME not set"), 1);
	return (0);
}

static int	cd_oldpwd(t_data *data)
{
	char	*pwd;

	pwd = read_env(data, "OLDPWD");
	if (pwd)
	{
		if (update_path(data, pwd))
			return (free(pwd), 1);
		free(pwd);
	}
	else
		return (print_error(NULL, "cd", "OLDPWD not set"), 1);
	return (0);
}

int	bcd(t_data *data, char **args)
{
	if (!args[0])
		return (cd_home(data));
	else if (!ft_strncmp(args[0], "-", 2))
		return (cd_oldpwd(data));
	else
		return (update_path(data, args[0]));
}
