/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:04:34 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/16 16:52:10 by molasz-a         ###   ########.fr       */
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
		ft_putendl_fd(read_env(data, "PWD"), 1);
	return (0);
}
