/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:44:13 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/16 19:21:31 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	run_builtin(t_data *data, int i, int ex)
{
	int	error;

	if (!ft_strncmp_case(data->coms[i].com[0], "cd", 3))
		error = bcd(data, data->coms[i].com + 1);
	else if (!ft_strncmp_case(data->coms[i].com[0], "echo", 5))
		error = becho(data->coms[i].com + 1);
	else if (!ft_strncmp_case(data->coms[i].com[0], "env", 4))
		error = benv(data);
	else if (!ft_strncmp_case(data->coms[i].com[0], "exit", 5))
		error = bexit(data, data->coms[i].com + 1);
	else if (!ft_strncmp_case(data->coms[i].com[0], "export", 7))
		error = bexport(data, data->coms[i].com + 1);
	else if (!ft_strncmp_case(data->coms[i].com[0], "pwd", 4))
		error = bpwd(data);
	else if (!ft_strncmp_case(data->coms[i].com[0], "unset", 6))
		error = bunset(data, data->coms[i].com + 1);
	else
		return (0);
	if (ex)
		exit(error);
	g_err = error;
	return (1);
}
