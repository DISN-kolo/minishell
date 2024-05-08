/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:45:13 by akozin            #+#    #+#             */
/*   Updated: 2024/05/08 16:59:41 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_latest_hd(t_token *ts)
{
	int	i;

	i = 0;
	while (ts[i].token)
	{
		if (ts[i].type == PIPE || ts[i].type == OR || ts[i].type == AND)
			return (1);
		else if (ts[i].type == HDOC)
			return (0);
		i++;
	}
	return (1);
}
