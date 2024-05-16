/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:40:31 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/16 17:06:41 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_handler(t_data *data, int exit_code)
{
	data_cleaner(data);
	free_env(data->env);
	exit(exit_code);
}

static int	numeric_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	bexit(t_data *data, char **args)
{
	if (!args || !args[0])
	{
		ft_putendl_fd("exit", 1);
		exit_handler(data, 0);
	}
	if (numeric_str(args[0]))
	{
		ft_putendl_fd("exit", 1);
		print_error("minishell: exit", args[0], "numeric argument required");
		exit_handler(data, 255);
	}
	else if (ft_strslen(args) > 1)
		return (print_error(NULL, "exit", "too many arguments"), 1);
	else
	{
		ft_putendl_fd("exit", 1);
		exit_handler(data, ft_atoi(args[0]));
	}
	return (0);
}
