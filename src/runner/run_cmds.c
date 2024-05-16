/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:34:21 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/16 17:19:37 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	run_builtin(t_data *data, int i, int ex)
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
		bpwd(data);
	else if (!ft_strncmp_case(data->coms[i].com[0], "unset", 6))
		bunset(data, data->coms[i].com + 1);
	else
		return (0);
	if (ex)
		exit(0);
	return (1);
}

static pid_t	one_cmd(t_data *data)
{
	pid_t	pid;

	if (data->coms[0].infd != -42 && dup2(data->coms[0].infd, 0) < 0)
		return (print_perror("Dup in one cmd redirect", -1), -1);
	if (data->coms[0].outfd != -42 && dup2(data->coms[0].outfd, 1) < 0)
		return (print_perror("Dup out one cmd redirect", -1), -1);
	if (!run_builtin(data, 0, 0))
	{
		pid = fork();
		if (pid < 0)
			return (print_perror("Fork one", -1), -1);
		else if (!pid)
		{
			default_sigs();
			find_cmd(data, 0);
		}
		return (pid);
	}
	return (-1);
}

static int	normal_pipe(t_data *data, int *end, int i, pid_t *pid)
{
	if (pipe(end) < 0)
		return (print_perror("Pipe", -1), 1);
	*pid = fork();
	if (*pid < 0)
		return (print_perror("Fork normal", -1), 1);
	else if (!*pid)
	{
		default_sigs();
		if (data->coms[i].outfd != -42 && dup2(data->coms[i].outfd, 1) < 0)
			print_perror("Dup out on child redirect", 1);
		else if (data->coms[i].outfd == -42 && dup2(end[1], 1) < 0)
			print_perror("Dup out on child pipe", 1);
		if (close(end[0]) < 0 || close(end[1]) < 0)
			print_perror("Close end on child", 1);
		if (!run_builtin(data, i, 1))
			find_cmd(data, i);
	}
	close(0);
	if (data->coms[i + 1].infd != -42 && dup2(data->coms[i + 1].infd, 0) < 0)
		return (print_perror("Dup in on parent redirect", -1), -1);
	else if (data->coms[i + 1].infd == -42 && dup2(end[0], 0) < 0)
		return (print_perror("Dup in on parent pipe", -1), 1);
	if (close(end[0]) < 0 || close(end[1]) < 0)
		return (print_perror("Close end on parent", -1), 1);
	return (0);
}

static pid_t	last_pipe(t_data *data, int i)
{
	pid_t	pid;

	if (data->coms[i].outfd != -42 && dup2(data->coms[i].outfd, 1) < 0)
		return (print_perror("Dup out last cmd redirect", -1), -1);
	pid = fork();
	if (pid < 0)
		return (print_perror("Fork last", -1), -1);
	else if (!pid)
	{
		default_sigs();
	   	if (!run_builtin(data, i, 1))
			find_cmd(data, i);
	}
	close(0);
	return (pid);
}

int	run_cmds(t_data *data)
{
	int		i;
	int		end[2];
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	if (!data->coms[1].com)
		pid = one_cmd(data);
	else
	{
		i = 0;
		while (data->coms[i].com && data->coms[i + 1].com)
			normal_pipe(data, end, i++, &pid);
		pid = last_pipe(data, i);
	}
	i = -1;
	while (data->coms[++i].com)
	{
		if (waitpid(-1, &status, 0) == pid)
			g_err = status;
	}
	if (WIFEXITED(status))
		g_err = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
		else if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 2);
		g_err = WTERMSIG(status) + 128;
	}
	return (free_coms(data->coms), data->coms = NULL, g_err);
}
