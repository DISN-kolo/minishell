/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:40:31 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/19 13:01:54 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exit_handler(t_data *data, int exit_code)
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

void	bexit(t_data *data, char **args)
{
	if (!args[0])
	{
		printf("exit\n");
		exit_handler(data, 0);
	}
	if (numeric_str(args[0]))
	{
		printf("exit\n");
		write(2, "minishell: exit: ", 17);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": numeric argument required\n", 28);
		exit_handler(data, 255);
	}
	else if (ft_strslen(args) > 1)
		write(2, "minishell: exit: too many arguments\n", 36);
	else
	{
		printf("exit\n");
		exit_handler(data, ft_atoi(args[0]));
	}
}
