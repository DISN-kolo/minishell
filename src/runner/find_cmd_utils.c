/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:44:13 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/20 17:20:45 by akozin           ###   ########.fr       */
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

static t_error	normal_pipe(t_data *data, int *end, int i, pid_t *pid)
{
	if (pipe(end) < 0)
		return (PIPE_ERR);
	*pid = fork();
	if (*pid < 0)
		return (FORK_ERR);
	else if (!*pid)
	{
		default_sigs();
		if (data->coms[i].outfd != -42 && dup2(data->coms[i].outfd, 1) < 0)
			print_perror("Dup out on child redirect", 1);
		else if (data->coms[i].outfd == -42 && dup2(end[1], 1) < 0)
			print_perror("Dup out on child pipe", 1);
		if (close(end[0]) < 0 || close(end[1]) < 0)
			print_perror("Close end on child", 1);
		if (!data->coms[i].com[0] || data->coms[i].amb_redir_ind >= 0)
			exit(0);
		if (!run_builtin(data, i, 1))
			find_cmd(data, i);
	}
	close(0);
	return (NULL_ERR);
}

static pid_t	last_pipe(t_data *data, int i)
{
	pid_t	pid;

	if (data->coms[i].outfd != -42 && dup2(data->coms[i].outfd, 1) < 0)
		return (data->aux_error = DUP2_ERR, -1);
	pid = fork();
	if (pid < 0)
		return (print_perror("Fork last", -1), -1);
	else if (!pid)
	{
		default_sigs();
		if (!data->coms[i].com[0] || data->coms[i].amb_redir_ind >= 0)
			exit (0);
		if (!run_builtin(data, i, 1))
			find_cmd(data, i);
	}
	close(0);
	return (pid);
}

pid_t	run_cmd_multiple(t_data *data, int *end)
{
	int		i;
	pid_t	pid;
	t_error	err;

	i = 0;
	while (data->coms[i].com && data->coms[i + 1].com)
	{
		err = normal_pipe(data, end, i++, &pid);
		if (err != NULL_ERR)
			return (data->aux_error = err, -1);
		printf("%d\n", data->coms[i + 1].infd);
		if (data->coms[i + 1].infd != -42 && dup2(data->coms[i + 1].infd, 0) < 0)
			return (printf("B\n"), data->aux_error = DUP2_ERR, -1);
		else if (data->coms[i + 1].infd == -42 && dup2(end[0], 0) < 0)
			return (data->aux_error = DUP2_ERR, 1);
		if (close(end[0]) < 0 || close(end[1]) < 0)
			return (data->aux_error = CLOSE_ERR, 1);
	}
	pid = last_pipe(data, i);
	return (pid);
}
