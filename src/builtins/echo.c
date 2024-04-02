/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:44:48 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/31 13:56:08 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	becho(char **args)
{
	int	i;
	int	n;

	if (!ft_strncmp(args[0], "-n", 3))
		n = 1;
	else
		n = 0;
	i = n;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, " ", 1);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
}
