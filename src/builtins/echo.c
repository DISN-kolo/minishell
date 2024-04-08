/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:44:48 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/02 16:49:06 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_nflag(char *arg)
{
	int	i;

	if (!arg && arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	becho(char **args)
{
	int	i;
	int	n;

	i = 0;
	while (args[i] && is_nflag(args[i]))
		i++;
	n = 0;
	if (i)
		n = 1;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, " ", 1);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
}
