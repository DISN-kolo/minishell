/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:16:20 by akozin            #+#    #+#             */
/*   Updated: 2024/03/28 15:40:39 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	tokenize_line(char *s, t_data *data)
{
	if (data->errored)
		return ;
	printf("n of 'tokens' is %3d\n", tokenize_count(s, " \t\f\v"));
	data->tokens = tokenize_split(s);
	printf("%p\n", data->tokens);
	if (!data->tokens || tokenize_err_probe(data->tokens))
	{
		data->errored = 1;
		return ;
	}
	for (int i = 0; data->tokens[i].token; i++)
		printf("'token' number   %3d: %s\n", i, data->tokens[i].token);
}
