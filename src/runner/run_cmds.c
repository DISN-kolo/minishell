/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:34:21 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/10 11:42:21 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_builtins(t_data *data, int i)
{
	if (data->coms[i].com)
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
		return (1);
	}
	return (0);
}

static int	find_cmd(void)
{
	write(2, "HI\n", 3);
	return (0);
}

int	run_cmds(t_data *data)
{
	int		i;

	i = 0;
	while (data->coms[i].com)
	{
		if (!check_builtins(data, i))
			find_cmd();
		i++;
	}
	return (0);
}
