/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:34:21 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/14 20:19:39 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*remove_brackets(t_token *tokens)
{
	int		len;

	len = tokens_len(tokens);
	return (tokens_list(tokens + 1, len - 2));
}

static pid_t	one_cmd(t_data *data, t_token *tokens)
{
	pid_t	pid;

	if (data->coms[0].infd != -42 && dup2(data->coms[0].infd, 0) < 0)
		return (print_perror("Dup in one cmd redirect", -1), -1);
	if (data->coms[0].outfd != -42 && dup2(data->coms[0].outfd, 1) < 0)
		return (print_perror("Dup out one cmd redirect", -1), -1);
	if (tokens[0].type != O_BRACKET &&!run_builtin(data, 0, 0))
	{
		printf("HI %s\n", tokens[0].token);
		pid = fork();
		if (pid < 0)
			return (print_perror("Fork one cmd", -1), -1);
		else if (!pid)
		{
			if (tokens[0].type == O_BRACKET)
				return (token_recursive_loop(data, remove_brackets(tokens)), -1);
			find_cmd(data, 0);
		}
		return (pid);
	}
	return (-1);
}

static int	normal_pipe(t_data *data, t_token *tokens, int *end, int i, pid_t *pid)
{
	if (pipe(end) < 0)
		return (print_perror("Pipe", -1), 1);
	*pid = fork();
	if (*pid < 0)
		return (print_perror("Fork normal", -1), 1);
	else if (!*pid)
	{
		if (data->coms[i].outfd != -42 && dup2(data->coms[i].outfd, 1) < 0)
			print_perror("Dup out on child redirect", 1);
		else if (data->coms[i].outfd == -42 && dup2(end[1], 1) < 0)
			print_perror("Dup out on child pipe", 1);
		if (close(end[0]) < 0 || close(end[1]) < 0)
			print_perror("Close end on child", 1);
		if (tokens[0].type == O_BRACKET)
			return (token_recursive_loop(data, tokens), -1);
		else if (!run_builtin(data, i, 1))
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
	else if (!pid && !run_builtin(data, i, 1))
		find_cmd(data, i);
	close(0);
	return (pid);
}

int	run_cmds(t_data *data, t_token *tokens)
{
	int		i;
	int		end[2];
	int		status;
	pid_t	pid;

	if (!data->coms[1].com)
		pid = one_cmd(data, tokens);
	else
	{
		i = -1;
		printf("TOKENS: %s %s %s\n", tokens[0].token, tokens[1].token, tokens[2].token);
		while (data->coms[++i].com && data->coms[i + 1].com)
			normal_pipe(data, tokens + i, end, i, &pid);
		pid = last_pipe(data, i);
	}
	i = -1;
	while (data->coms[++i].com)
	{
		if (waitpid(-1, &status, 0) == pid)
			data->status_code = status;
	}
	if (pid < 0)
		data->status_code = 0;
	return (0);
}
