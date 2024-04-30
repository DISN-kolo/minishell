/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:33:56 by akozin            #+#    #+#             */
/*   Updated: 2024/04/30 14:31:07 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libs/gnl/get_next_line.h"

int	heredoc_read_expand(int *i, t_data *data)
{
	char	*fname;
	char	curline;
	int		hdfd;

	fname = gen_h_fname(i[0], data->hd_counter);
	printf("HEREDOC fname: '%s', on %d\n", fname, data->hd_counter);
	hdfd = open(fname, O_RDONLY);
	curline = get_next_line(hdfd);
	while (curline)

	return (-2);
}
