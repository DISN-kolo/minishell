/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:34:21 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/18 16:17:33 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	run_cmd(t_data *data, int i)
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
		find_cmd(data, i);
	exit(0);
}

static void	one_cmd(t_data *data)
{
	pid_t	pid;

	if (!ft_strncmp_case(data->coms[0].com[0], "cd", 3))
		bcd(data, data->coms[0].com + 1);
	else if (!ft_strncmp_case(data->coms[0].com[0], "echo", 5))
		becho(data->coms[0].com + 1);
	else if (!ft_strncmp_case(data->coms[0].com[0], "env", 4))
		benv(data);
	else if (!ft_strncmp_case(data->coms[0].com[0], "exit", 5))
		bexit(data, data->coms[0].com + 1);
	else if (!ft_strncmp_case(data->coms[0].com[0], "export", 7))
		bexport(data, data->coms[0].com + 1);
	else if (!ft_strncmp_case(data->coms[0].com[0], "pwd", 4))
		bpwd(data, data->coms[0].com + 1);
	else if (!ft_strncmp_case(data->coms[0].com[0], "unset", 6))
		bunset(data, data->coms[0].com + 1);
	else
	{
		pid = fork();
		if (pid < 0)
			write(2, "Fork pipe error\n", 16);
		else if (!pid)
			find_cmd(data, 0);
	}
}

static pid_t	normal_pipe(t_data *data, int *end, int i)
{
	pid_t	pid;

	if (pipe(end) < 0)
		write(2, "Pipe error\n", 11);
	pid = fork();
	if (pid < 0)
		write(2, "Fork pipe error\n", 16);
	else if (!pid)
	{
		if (dup2(end[1], 1) < 0)
			write(2, "Child dup end[1] error\n", 23);
		if (close(end[0]) < 0)
			write(2, "Child close end[0] error\n", 25);
		run_cmd(data, i);
	}
	if (dup2(end[0], 0) < 0)
		write(2, "Parent dup end[0] error\n", 24);
	if (close(end[1]) < 0)
		write(2, "Parent close end[1] error\n", 26);
	return (pid);
}

static pid_t	last_pipe(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		write(2, "Fork pipe error\n", 16);
	else if (!pid)
		run_cmd(data, i);
	return (pid);
}

int	run_cmds(t_data *data)
{
	int		i;
	int		end[2];
	int		status;
	pid_t	pid;

	data->std_in = dup(STDIN_FILENO);
	if (!data->coms[1].com)
		one_cmd(data);
	else
	{
		i = 0;
		while (data->coms[i].com && data->coms[i + 1].com)
			normal_pipe(data, end, i++);
		pid = last_pipe(data, i);
	}
	i = -1;
	while (data->coms[++i].com)
		waitpid(-1, &status, 0);
	dup2(data->std_in, STDIN_FILENO);
	return (0);
}
