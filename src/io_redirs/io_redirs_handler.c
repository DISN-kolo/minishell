/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirs_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:31 by akozin            #+#    #+#             */
/*   Updated: 2024/05/01 16:56:41 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * rewrite this with the new ios array of ins and outs at the same time
 * TODO
 * i[0] - com c
 * i[1] - io c
 *
 * j -- hd coords
 */
int	open_everything(t_data *data)
{
	int	i[2];
	int	j[2];
	int	fi;
	int	fo;
	int	flags;

	i[0] = 0;
	if (!data->coms)
		return (-3); // 0 coms in a comm, like '< asd'
	while (data->coms[i[0]].com)
	{
		printf("open everything cycle: i0 = %d\n", i[0]);
		data->coms[i[0]].infd = -42;
		data->coms[i[0]].outfd = -42;
		i[1] = 0;
		fi = -42;
		fo = -42;
		while (data->coms[i[0]].ios[i[1]].fname)
		{
			printf("\t'fname' = '%s'\n", data->coms[i[0]].ios[i[1]].fname);
			if (data->coms[i[0]].ios[i[1]].amb || i[1] == data->coms[i[0]].amb_redir_ind)
			{
				printf("ALRIGHT STOP\n");
				break ; // TODO aight, stop
			}
			if (data->coms[i[0]].ios[i[1]].in)
			{
				printf("\tin-opening on i[1] = %d\n", i[1]);
				if (fi != -42)
					close(fi);
				if (data->coms[i[0]].ios[i[1]].dub)
				{
					printf("HD detected\n");
//					fi = -420;
					hd_coords(j, data->hd_counter, data);
					if (data->hds[j[0]][j[1]].latest)
						fi = heredoc_read_expand(data); // TODO can return -2
					data->hd_counter++;
				}
				else
					fi = open(data->coms[i[0]].ios[i[1]].fname, O_RDONLY);
				if (fi == -1)
					return (-2); // TODO non-fatal error, such as "no such file or directory"
				else if (fi == -2)
					return (-1); // TODO fatal error(?). someone screwed our heredoc tmp file!
			}
			else
			{
				printf("\tout-opening on i[1] = %d\n", i[1]);
				if (fo != -42)
					close(fo);
				if (data->coms[i[0]].ios[i[1]].dub)
					flags = O_WRONLY | O_CREAT | O_APPEND;
				else
					flags = O_WRONLY | O_CREAT | O_TRUNC;
				fo = open(data->coms[i[0]].ios[i[1]].fname, flags, 0644);
				if (fo == -1)
					return (-2); // TODO non-fatal error. move on to the next command
			}
			i[1]++;
		}
		if (i[1] && !data->coms[i[0]].ios[i[1] - 1].amb
				&& i[1] != data->coms[i[0]].amb_redir_ind)
		{
			data->coms[i[0]].infd = fi;
			data->coms[i[0]].outfd = fo;
		}
		else
		{
			close(fi);
			close(fo);
		}
		i[0]++;
	}
	printf("exiting io redirs hadler with amb tok ind: %d\n", data->amb_tok_ind);
	return (data->amb_tok_ind != -42); // TODO better error code for amb redir
}
