/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_rl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:13:57 by akozin            #+#    #+#             */
/*   Updated: 2024/05/15 16:46:07 by akozin           ###   ########.fr       */
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
		if (hline && !ft_strncmp(hline, eof, eoflen + 1))
			break ;
		if (hline && write(fd, hline, ft_strlen(hline)) == -1)
			return (1);
		if (hline && write(fd, "\n", 1) == -1)
			return (1);
		if (hline)
			free(hline);
		hline = readline("> ");
		if (!hline)
			return (0);
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
		fname = gen_h_fname(i);
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
		if (grab_and_write_hdoc(fd, data->hds[i[0]][i[1]].str))
		{
			close(fd);
			exit(1);
		}
		close(fd);
		free(fname);
	}
	else if (fake_heredoc(data->hds[i[0]][i[1]].str))
		exit(1);
	return (0);
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
		i[0]++;
	}
	exit(0);
}

static int	wifstuff(int status, t_data *data)
{
	if (WIFEXITED(status))
	{
		if (status == 256)
			data->status_code = 1;
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT))
		return (1);
	return (0);
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
		return (print_perror("Fork heredocs", 1), 1);
	if (pid == 0)
		hd_fork(data, i);
	else
		signal(SIGINT, SIG_IGN);
	wait(&status);
	printf("\n\n%d\n\n", status);
	return (wifstuff(status, data));
}
