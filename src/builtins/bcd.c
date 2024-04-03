/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bcd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:06:05 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/03 14:25:49 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_pwd(t_data *data, char *path, int envi)

void	update_path(t_data *data, char *path, int envi)
{
	if (chdir(path) < 0)
		write(2, "CHDIR error\n", 12);
	else
	{
		export_env(data, );
	}
}

void	bcd(t_data *data, char **args, int envi)
{
	char	*path;

	if (!args[0])
		update_path(data, read_env(data, "HOME", envi), envi);
	else if (args[0][0] == '/')
		update_path(data, args[0], envi);
	else
	{
		path = ft_strjoin(read_env(data, "PWD", envi), args[0]);
		if (!path)
			return ;
		update_path(data, path, envi);
		free(path);
	}
}
