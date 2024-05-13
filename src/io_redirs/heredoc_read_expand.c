/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:33:56 by akozin            #+#    #+#             */
/*   Updated: 2024/05/13 16:24:51 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libs/gnl/get_next_line.h"

void	hd_coords(int *hdi, int n, t_data *data)
{
	int	x;

	x = 0;
	hdi[0] = 0;
	hdi[1] = 0;
	while (x < n)
	{
		if (data->hds[hdi[0]])
		{
			if (data->hds[hdi[0]][hdi[1]].str)
			{
				if (data->hds[hdi[0]][hdi[1] + 1].str)
					hdi[1]++;
				else
				{
					if (data->hds[hdi[0] + 1])
					{
						hdi[1] = 0;
						hdi[0]++;
					}
				}
			}
		}
		x++;
	}
}

static int	gnl_expand(t_data *data, char *fname, int hdfd)
{
	int		susfd;
	char	*curline;

	fname = ft_strjoin_free(fname, "_exp");
	susfd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (susfd == -1)
		return (print_perror("Open failed in hdoc sust\n", -1), -2); // TODO think twice
	curline = get_next_line(hdfd);
	while (curline)
	{
		curline = hd_dollar_expander(curline, data);
		if (write(susfd, curline, ft_strlen(curline)) == -1)
			return (print_perror("Write failed in hdoc sust\n", -1), -2); // TODO think twice
		free(curline);
		curline = get_next_line(hdfd);
	}
	if (curline)
		free(curline);
	close(susfd);
	printf("%s <- fname after all the good stuff and before exiting\n", fname);
	return (0);
}

int	heredoc_read_expand(t_data *data)
{
	char	*fname;
	int		hdfd;
	int		hdi[2];

	hd_coords(hdi, data->hd_counter, data);
	fname = gen_h_fname(hdi);
	hdfd = open(fname, O_RDONLY);
	if (hdfd == -1)
		return (print_perror("Open failed in hdoc\n", -1), -2); // TODO think twice abt the err code
	if (data->hds[hdi[0]][hdi[1]].expand)
	{
		if (gnl_expand(data, fname, hdfd) == -2)
			return (-2);
		close(hdfd);
		printf("%s <- fname after all the good stuff\n", fname);
		hdfd = open(fname, O_RDONLY);
		if (hdfd == -1)
			return (print_perror("Second open failed in hdoc\n", -1), -2); // TODO think twice
	}
	free(fname);
	return (hdfd);
}
