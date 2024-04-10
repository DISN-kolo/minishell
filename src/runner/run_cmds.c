/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:34:21 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/10 11:10:31 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_builtins(t_data *data, t_com cmd)
{
	if (!ft_strncmp_case(cmd.com[0], "cd", 3))
		bcd(data, cmd.com + 1);
	else if (!ft_strncmp_case(cmd.com[0], "echo", 5))
		becho(cmd.com + 1);
	else if (!ft_strncmp_case(cmd.com[0], "env", 4))
		benv(data);
	else if (!ft_strncmp_case(cmd.com[0], "exit", 5))
		bexit(data, cmd.com + 1);
	else if (!ft_strncmp_case(cmd.com[0], "export", 7))
		bexport(data, cmd.com + 1);
	else if (!ft_strncmp_case(cmd.com[0], "pwd", 4))
		bpwd(data, cmd.com + 1);
	else if (!ft_strncmp_case(cmd.com[0], "unset", 6))
		bunset(data, cmd.com + 1);
	else
		return (0);
	return (1);
}

static int	find_cmd()
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
		if (!check_builtins(data, data->coms[i]))
			find_cmd();
		i++;
	}
	return (0);
}
