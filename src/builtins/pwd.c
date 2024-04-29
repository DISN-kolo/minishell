/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:04:34 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/29 15:13:51 by molasz-a         ###   ########.fr       */
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
			printf("%s\n", path);
			free(path);
		}
		else
			printf("%s\n", read_env(data, "PWD"));
	}
}
