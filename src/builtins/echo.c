/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:44:48 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/29 14:03:09 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_nflag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || !ft_strncmp(arg, "-", 2))
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
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putendl_fd("", 1);
}
