/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirs_handler_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:41:03 by akozin            #+#    #+#             */
/*   Updated: 2024/05/13 15:02:12 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_or_close_fds(t_data *data, int *i, int *fio)
{
	if (i[1] && !data->coms[i[0]].ios[i[1] - 1].amb
			&& i[1] != data->coms[i[0]].amb_redir_ind)
	{
		data->coms[i[0]].infd = fio[0];
		data->coms[i[0]].outfd = fio[1];
	}
	else
	{
		if (fio[0] != -42)
			close(fio[0]);
		if (fio[1] != -42)
			close(fio[1]);
	}
}
