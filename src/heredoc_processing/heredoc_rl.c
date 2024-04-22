/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_rl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:13:57 by akozin            #+#    #+#             */
/*   Updated: 2024/04/22 14:32:19 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../readline/readline.h"
#include "../../readline/history.h"

/*
 * i[0] goes thru the first array, which contains hds as arrays between operators,
 * i.e. &&s and ||s.
 * i[1] goes thru the second arrays, getting each heredoc.
 * j[0] goes thru the commands, j[1] goes thru their ins.
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
			fd = open(fname, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC);
			if (fd == -1)
				printf("open errorred on %s\n", fname);
			//grab_and_write_hdoc(fd, ); // TODO
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
			unlink(fname);
			free(fname);
			i[1]++;
		}
		printf("==\n");
		i[0]++;
	}
//
//
//	int		i;
//	char	*hline;
//
//	i = 0;
//	hline = readline("> ");
//	while (hline && ft_strncmp(hline, "forcedoc", 8))
//	{
//		printf("last line was '%s'\n", hline);
//		hline = readline("> ");
//		if (!data->hds)
//			return (1);
//	}
	return (0);
}
