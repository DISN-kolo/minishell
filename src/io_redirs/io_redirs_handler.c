/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirs_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:31 by akozin            #+#    #+#             */
/*   Updated: 2024/04/23 16:40:54 by akozin           ###   ########.fr       */
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
	int	fd;
	int	flags;

	i[0] = 0;
	while (data->coms[i[0]].com)
	{
		data->coms[i[0]].infd = 0;
		data->coms[i[0]].outfd = 1;
		i[1] = 0;
		while (data->coms[i[0]].ins[i[1]].fname)
		{
			if (data->coms[i[0]].ins[i[1]].dub
					&& !data->coms[i[0]].ins[i[1] + 1].fname)
				fd = heredoc_read_expand(i, data); // TODO
			else if (!data->coms[i[0]].ins[i[1]].dub)
				fd = open(data->coms[i[0]].ins[i[1]].fname, O_RDONLY);
			if (fd == -1)
				return (-2); // TODO non-fatal error. move on to the next command
			else if (fd == -2)
				return (-1); // TODO fatal error(?). someone screwed our heredoc tmp file!
			if (data->coms[i[0]].ins[i[1] + 1].fname)
				close(fd);
			i[1]++;
		}
		i[1] = 0;
		while (data->coms[i[0]].outs[i[1]].fname)
		{
			if (data->coms[i[0]].outs[i[1]].dub)
				flags = O_WRONLY | O_CREAT | O_APPEND;
			else
				flags = O_WRONLY | O_CREAT | O_TRUNC;
			fd = open(data->coms[i[0]].outs[i[1]].fname, flags);
			if (data->coms[i[0]].outs[i[1] + 1].fname)
				close(fd);
			i[1]++;
		}
		data->coms[i[0]].outfd = fd;
		i[0]++;
	}
}
