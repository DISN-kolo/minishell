/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:45:13 by akozin            #+#    #+#             */
/*   Updated: 2024/05/08 12:33:17 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_latest_hd(t_token *ts)
{
	int	i;

	i = 0;
	while (ts[i].token)
	{
		if (!ft_strncmp(ts[i].token, "|", 2)
			|| !ft_strncmp(ts[i].token, "||", 3)
			|| !ft_strncmp(ts[i].token, "&&", 3))
			return (1);
		if (!ft_strncmp(ts[i].token, "<<", 3))
			return (0);
		i++;
	}
	return (1);
}
