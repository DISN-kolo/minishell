/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:44:13 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/14 19:59:45 by molasz-a         ###   ########.fr       */
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
	if (!ft_strncmp_case(data->coms[i].com[0], "cd", 3))
		bcd(data, data->coms[i].com + 1);
	else if (!ft_strncmp_case(data->coms[i].com[0], "echo", 5))
		becho(data->coms[i].com + 1);
	else if (!ft_strncmp_case(data->coms[i].com[0], "env", 4))
		benv(data);
	else if (!ft_strncmp_case(data->coms[i].com[0], "exit", 5))
		bexit(data, data->coms[i].com + 1);
	else if (!ft_strncmp_case(data->coms[i].com[0], "export", 7))
		bexport(data, data->coms[i].com + 1);
	else if (!ft_strncmp_case(data->coms[i].com[0], "pwd", 4))
		bpwd(data, data->coms[i].com + 1);
	else if (!ft_strncmp_case(data->coms[i].com[0], "unset", 6))
		bunset(data, data->coms[i].com + 1);
	else
		return (0);
	if (ex)
		exit(0);
	return (1);
}

