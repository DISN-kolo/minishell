/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:19:46 by akozin            #+#    #+#             */
/*   Updated: 2024/03/27 13:06:11 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * TODO
 * make all of this sepped by funcs and norminette compliant n stuff
 */
void	parse_line(t_data *data)
{
	char	*onecom;

	onecom = malloc(one_com_len_c(data, i)); //TODO int one_com_len_c(t_data *data, int first)
	if (!onecom)
		return ; //TODO erroring out
	one_com_filler(data, i, &onecom); //TODO (int for error?) void one_com_filler(t_data *data, int i,)
	if (data->errored)
		return ;
}
