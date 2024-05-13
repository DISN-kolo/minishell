/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirs_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:31 by akozin            #+#    #+#             */
/*   Updated: 2024/05/13 15:17:44 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	infile_handling(t_data *data, int *i, int *fio)
{
	int	j[2];

	if (fio[1] != -42)
		close(fio[1]);
	if (data->coms[i[0]].ios[i[1]].dub)
	{
		hd_coords(j, data->hd_counter, data);
		if (data->hds[j[0]][j[1]].latest)
			fio[1] = heredoc_read_expand(data); // TODO can return -2
		data->hd_counter++;
	}
	else
		fio[1] = open(data->coms[i[0]].ios[i[1]].fname, O_RDONLY);
	if (fio[1] == -1)
		return (-2); // TODO non-fatal error, such as "no such file or directory"
	else if (fio[1] == -2)
		return (-1); // TODO fatal error(?). someone screwed our heredoc tmp file!
	return (0);
}

static int	outfile_handling(t_data *data, int *i, int *fio)
{
	int	flags;

	if (fio[1] != -42)
		close(fio[1]);
	if (data->coms[i[0]].ios[i[1]].dub)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fio[1] = open(data->coms[i[0]].ios[i[1]].fname, flags, 0644);
	if (fio[1] == -1)
		return (-2); // TODO non-fatal error. move on to the next command
	return (0);
}

static int	io_decide_handle(t_data *data, int *i, int *fio)
{
	int	retcode;

	if (data->coms[i[0]].ios[i[1]].in)
	{
		retcode = infile_handling(data, i, fio);
		if (retcode)
			return (retcode);
	}
	else
	{
		retcode = outfile_handling(data, i, fio);
		if (retcode)
			return (retcode);
	}
	return (0);
}

static void	open_everything_init(t_data *data, int *i, int *fio)
{
	data->coms[i[0]].infd = -42;
	data->coms[i[0]].outfd = -42;
	i[1] = 0;
	fio[0] = -42;
	fio[1] = -42;
}

/*
 * rewrite this with the new ios array of ins and outs at the same time
 * TODO
 * i[0] - com c
 * i[1] - io c
 *
 * fio[0] - fi
 * fio[1] - fo
 *
 * j -- hd coords
 *
 * i suppose a better thing is on the way once the ()&&|| thing is done
 */
int	open_everything(t_data *data)
{
	int	i[2];
	int	fio[2];
	int	retcode;

	i[0] = 0;
	if (!data->coms)
		return (-3); // 0 coms in a comm, like '< asd'
	while (data->coms[i[0]].com)
	{
		open_everything_init(data, i, fio);
		while (data->coms[i[0]].ios[i[1]].fname)
		{
			if (data->coms[i[0]].ios[i[1]].amb
				|| i[1] == data->coms[i[0]].amb_redir_ind)
				break ;
			// TODO aight, stop
			retcode = io_decide_handle(data, i, fio);
			if (retcode)
				return (retcode);
			i[1]++;
		}
		set_or_close_fds(data, i, fio);
		i[0]++;
	}
	return (data->amb_tok_ind != -42); // TODO better error code for amb redir
}
