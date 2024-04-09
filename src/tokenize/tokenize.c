/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:16:20 by akozin            #+#    #+#             */
/*   Updated: 2024/04/09 14:09:33 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	tokenize_line(char *s, t_data *data)
{
	if (data->errored)
		return ;
	data->tokens = tokenize_split(s);
	if (!data->tokens || tokenize_err_probe(data->tokens))
	{
		data->errored = 1;
		return ;
	}
}
