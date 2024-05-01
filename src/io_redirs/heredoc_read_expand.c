/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:33:56 by akozin            #+#    #+#             */
/*   Updated: 2024/05/01 15:34:03 by akozin           ###   ########.fr       */
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

int	heredoc_read_expand(t_data *data)
{
	char	*fname;
	char	*curline;
	int		hdfd;
	int		hdi[2];

	hd_coords(hdi, data->hd_counter, data);
	fname = gen_h_fname(hdi);
	printf("HEREDOC fname: '%s', on %d (which is %2d %2d)\n", fname, data->hd_counter, hdi[0], hdi[1]);
	hdfd = open(fname, O_RDONLY);
	curline = get_next_line(hdfd);
	while (curline)
	{
		printf("gnl from %s:\n'%s'\n", fname, curline);
		if (data->hds[hdi[0]][hdi[1]].expand)
			curline = hd_dollar_expander(curline, data);
		printf("sussed:\n'%s'\n", curline);
		free(curline);
		curline = get_next_line(hdfd);
	}
	if (curline)
		free(curline);
	return (hdfd);
}
