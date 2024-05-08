/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_rl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:13:57 by akozin            #+#    #+#             */
/*   Updated: 2024/05/08 13:03:46 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libs/readline/readline.h"
#include "../../libs/readline/history.h"

static int	grab_and_write_hdoc(int fd, char *eof)
{
	int		eoflen;
	char	*hline;

	eoflen = ft_strlen(eof);
	hline = NULL;
	while (1)
	{
		if (hline && write(fd, hline, ft_strlen(hline)) == -1)
			return (1);
		if (hline && write(fd, "\n", 1) == -1)
			return (1);
		if (hline && !ft_strncmp(hline, eof, eoflen + 1))
			break ;
		if (hline)
			free(hline);
		hline = readline("> ");
		if (!hline)
			return (1);
	}
	if (hline)
		free(hline);
	return (0);
}

static int	fake_heredoc(char *eof)
{
	int		eoflen;
	char	*hline;

	eoflen = ft_strlen(eof);
	hline = NULL;
	while (1)
	{
		if (hline && !ft_strncmp(hline, eof, eoflen + 1))
			break ;
		if (hline)
			free(hline);
		hline = readline("> ");
		if (!hline)
			return (1);
	}
	if (hline)
		free(hline);
	return (0);
}

static int	process_heredoc(t_data *data, int *i)
{
	int		fd;
	char	*fname;

	if (data->hds[i[0]][i[1]].latest)
	{
		printf("data->hds[%2d][%2d].str = '%s', exp: %d\n", i[0], i[1], data->hds[i[0]][i[1]].str, data->hds[i[0]][i[1]].expand);
		fname = gen_h_fname(i);
		if (access(fname, F_OK) == 0)
			printf("why do we have the %s file already?\n", fname);
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC);
		if (fd == -1)
		{
			printf("open errorred on %s\n", fname);
			exit(1);
		}
		if (grab_and_write_hdoc(fd, data->hds[i[0]][i[1]].str))
		{
			close(fd);
			printf("write failed\n");
			exit(1);
		}
		close(fd);
		free(fname);
	}
	else if (fake_heredoc(data->hds[i[0]][i[1]].str))
	{
		printf("fake heredoc failed\n");
		exit(1);
	}
	exit(0);
}

static int	hd_fork(t_data *data, int *i)
{
	signal(SIGINT, handle_s_hered);
	signal(SIGQUIT, SIG_IGN);
	i[0] = 0;
	while (data->hds[i[0]])
	{
		i[1] = 0;
		while (data->hds[i[0]][i[1]].str)
		{
			if (process_heredoc(data, i))
				exit(1);
			i[1]++;
		}
		printf("== one heredoc processed...\n");
		i[0]++;
	}
	exit(0);
}

/*
 * i[0] goes thru the first array, which contains hds as arrays between
 *+operators, i.e. &&s and ||s.
 * i[1] goes thru the second arrays, getting each heredoc.
 * actually we'd only need the last heredoc. so.... an if which avoids
 *+creating files if we don't use them.
 */
int	process_heredocs(t_data *data)
{
	int		i[2];
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return(print_perror("Fork heredocs", 1), 1);
	if (pid == 0)
		hd_fork(data, i);
	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT))
		return (1);
	return (0);
}
