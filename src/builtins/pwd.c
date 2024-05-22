/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:04:34 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/22 11:46:20 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bpwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putendl_fd(path, 1);
		free(path);
	}
	else
	{
		path = read_env(data, "PWD");
		if (!path)
			return (1);
		ft_putendl_fd(path, 1);
		free(path);
	}
	return (0);
}
