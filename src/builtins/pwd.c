/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:04:34 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/01 12:42:14 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bpwd(t_data *data, char **args)
{
	char	*path;

	if (ft_strslen(args))
		ft_putendl_fd("pwd: too many arguments", 2);
	else
	{
		path = getcwd(NULL, 0);
		if (path)
		{
			ft_putendl_fd(path, 1);
			free(path);
		}
		else
			ft_putendl_fd(read_env(data, "PWD"), 1);
	}
}
