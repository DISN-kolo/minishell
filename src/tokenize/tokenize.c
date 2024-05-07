/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:16:20 by akozin            #+#    #+#             */
/*   Updated: 2024/05/07 16:39:02 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	tokenize_line(char *s, t_data *data)
{
	int	i;

	if (data->errored)
		return ;
	data->tokens = tokenize_split(s);
	i = -1;
	while (data->tokens[++i].token)
		data->tokens[i].type = determine_type(data->tokens[i].token);
	if (!data->tokens || tokenize_err_probe(data->tokens))
	{
		data->errored = 1;
		return ;
	}
}
