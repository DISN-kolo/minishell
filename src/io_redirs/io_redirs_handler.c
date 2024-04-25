/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirs_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:31 by akozin            #+#    #+#             */
/*   Updated: 2024/04/25 15:54:45 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * rewrite this with the new ios array of ins and outs at the same time
 * TODO
 */
int	open_everything(t_data *data)
{
	int	i[3];
	int	fi;
	int	fo;
	int	flags;

	i[0] = 0;
	while (data->coms[i[0]].com)
	{
		printf("i0 = %d\n", i[0]);
		data->coms[i[0]].infd = 0;
		data->coms[i[0]].outfd = 1;
		i[1] = 0;
		fi = -42;
		fo = -42;
		while (data->coms[i[0]].ios[i[1]].fname)
		{
			if (data->coms[i[0]].ios[i[1]].amb || i[1] == data->coms[i[0]].amb_redir_ind)
			{
				printf("ALRIGHT STOP\n");
				break ; // TODO aight, stop
			}
			if (data->coms[i[0]].ios[i[1]].in)
			{
				if (fi != -42)
					close(fi);
				if (data->coms[i[0]].ios[i[1]].dub
						&& !data->coms[i[0]].ios[i[1] + 1].fname)
					fi = -420;
//					fi = heredoc_read_expand(i, data); // TODO
				else if (!data->coms[i[0]].ios[i[1]].dub)
					fi = open(data->coms[i[0]].ios[i[1]].fname, O_RDONLY);
				if (fi == -1)
					return (-2); // TODO non-fatal error. move on to the next command
				else if (fi == -2)
					return (-1); // TODO fatal error(?). someone screwed our heredoc tmp file!
			}
			else
			{
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
		if (!data->coms[i[0]].ios[i[1]].amb && i[1] != data->coms[i[0]].amb_redir_ind)
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
	printf("btw, amb tok ind is %d\n", data->amb_tok_ind);
	return (data->amb_tok_ind != -42);
}
