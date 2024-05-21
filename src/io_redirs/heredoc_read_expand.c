/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:33:56 by akozin            #+#    #+#             */
/*   Updated: 2024/05/21 14:17:54 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libs/gnl/get_next_line.h"

static int	gnl_expand(t_data *data, char **fname, int hdfd)
{
	int		susfd;
	char	*curline;

	*fname = ft_strjoin_free(*fname, "_exp");
	if (!*fname)
		return (-1);
	susfd = open(*fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (susfd == -1)
		return (-2);
	curline = get_next_line(hdfd);
	while (curline)
	{
		curline = hd_dollar_expander(curline, data);
		if (!curline)
			return (-1);
		if (write(susfd, curline, ft_strlen(curline)) == -1)
			return (-2);
		free(curline);
		curline = get_next_line(hdfd);
	}
	if (curline)
		free(curline);
	close(susfd);
	return (0);
}

int	heredoc_read_expand(t_data *data)
{
	char	*fname;
	int		hdfd;
	int		hdi[2];
	int		err;

	hdi[0] = data->coms_ind;
	hdi[1] = data->hd_counter;
	fname = gen_h_fname(hdi);
	hdfd = open(fname, O_RDONLY);
	if (hdfd == -1)
		return (-2);
	if (data->hds[data->coms_ind][data->hd_counter].expand)
	{
		err = gnl_expand(data, &fname, hdfd);
		if (err)
			return (err);
		close(hdfd);
		hdfd = open(fname, O_RDONLY);
		if (hdfd == -1)
			return (-2);
	}
	free(fname);
	return (hdfd);
}
