/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:29:33 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/29 13:51:33 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	export_pwd(t_data *data, char *key, char *value)
{
	char	*export;

	export = ft_strjoin3(key, "=", value);
	if (!export)
		return (1);
	export_env(data, export);
	free(export);
	return (0);
}

static void	update_path(t_data *data, char *path)
{
	char	*pwd;

	if (chdir(path) < 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
	}
	else
	{
		pwd = read_env(data, "PWD");
		if (!pwd)
			return ;
		export_pwd(data, "OLDPWD", pwd);
		free(pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return ;
		export_pwd(data, "PWD", pwd);
		free(pwd);
	}
}

static void	cd_home(t_data *data)
{
	char	*home;

	home = read_env(data, "HOME");
	if (home)
	{
		update_path(data, home);
		free(home);
	}
	else
		print_error(NULL, "cd", "HOME not set");
}

static void	cd_oldpwd(t_data *data)
{
	char	*pwd;

	pwd = read_env(data, "OLDPWD");
	if (pwd)
	{
		update_path(data, pwd);
		free(pwd);
	}
	else
		print_error(NULL, "cd", "OLDPWD not set");
}

void	bcd(t_data *data, char **args)
{
	if (!args[0])
		cd_home(data);
	else if (!ft_strncmp(args[0], "-", 2))
		cd_oldpwd(data);
	else
		update_path(data, args[0]);
}
