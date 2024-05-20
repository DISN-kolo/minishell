/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:34:21 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/20 17:18:33 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static pid_t	one_cmd(t_data *data)
{
	pid_t	pid;

	if (!data->coms[0].com[0] || data->coms[0].amb_redir_ind >= 0)
		return (-1);
	if (data->coms[0].infd != -42 && dup2(data->coms[0].infd, 0) < 0)
		return (data->aux_error = DUP2_ERR, -1);
	if (data->coms[0].outfd != -42 && dup2(data->coms[0].outfd, 1) < 0)
		return (data->aux_error = DUP2_ERR, -1);
	if (!run_builtin(data, 0, 0))
	{
		pid = fork();
		if (pid < 0)
			return (data->aux_error = FORK_ERR, -1);
		else if (!pid)
		{
			default_sigs();
			find_cmd(data, 0);
		}
		return (pid);
	}
	return (-1);
}

static void	handle_signals(int status)
{
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
		if (data->coms[0].infd != -42 && dup2(data->coms[0].infd, 0) < 0)
			return (data->aux_error = DUP2_ERR, 1);
		pid = run_cmd_multiple(data, end);
	}
	i = -1;
	while (data->coms[++i].com && pid > 0)
	{
		if (waitpid(-1, &status, 0) == pid)
			g_err = status;
	}
	if (pid != -1)
		handle_signals(status);
	return (free_coms(data->coms), data->coms = NULL, 0);
}
