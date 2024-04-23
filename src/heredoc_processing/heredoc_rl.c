/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_rl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:13:57 by akozin            #+#    #+#             */
/*   Updated: 2024/04/23 12:41:04 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../readline/readline.h"
#include "../../readline/history.h"

static int	grab_and_write_hdoc(int fd, char *eof)
{
	int		i;
	int		eoflen;
	char	*hline;

	i = 0;
	eoflen = ft_strlen(eof);
	hline = readline("> ");
	while (hline && ft_strncmp(hline, eof, eoflen))
	{
		if (write(fd, hline, ft_strlen(hline)) == -1)
			return (1);
		if (write(fd, "\n", 1) == -1)
			return (1);
		hline = readline("> ");
	}
	return (0);
}

/*
 * i[0] goes thru the first array, which contains hds as arrays between
 * operators, i.e. &&s and ||s.
 * i[1] goes thru the second arrays, getting each heredoc.
 *
 * prolly only for cmd filler -> j[0] goes thru the commands,
 * j[1] goes thru their ins.
 *
 * i don't think we need a total counter.
 */
int	process_heredocs(t_data *data)
{
	int		i[2];
	char	*fname;
	int		fd;
//	int	j[2];

	if (data->errored)
		return (1);
	i[0] = 0;
//	j[0] = 0;
//	j[1] = 0;
	while (data->hds[i[0]])
	{
		i[1] = 0;
		while (data->hds[i[0]][i[1]].str)
		{
			printf("data->hds[%2d][%2d].str = '%s', exp: %d\n", i[0], i[1], data->hds[i[0]][i[1]].str, data->hds[i[0]][i[1]].expand);
			fname = gen_h_fname(i[0], i[1]);
			if (access(fname, F_OK) == 0)
				printf("why do we have the %s file already?\n", fname);
			fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC);
			if (fd == -1)
				return (printf("open errorred on %s\n", fname), close(fd), 1);
			if (grab_and_write_hdoc(fd, data->hds[i[0]][i[1]].str))
				return (printf("write failed\n"), close(fd), 1);
			close(fd);
			/*
			if (!data->coms[j[0]].ins[j[1] + 1].fname)
			{
				j[0]++;
				j[1] = 0;
			}
			else
				j[1]++;
			*/
			// unlink(fname);
			free(fname);
			i[1]++;
		}
		printf("==\n");
		i[0]++;
	}
	return (0);
}
