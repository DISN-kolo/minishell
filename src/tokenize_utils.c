/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:24:06 by akozin            #+#    #+#             */
/*   Updated: 2024/03/25 12:51:09 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	valid_operator(char *s, int *i)
{
	char	remember_me;

	if (s[*i] == '&')
	{
		(*i)++;
		if (s[*i] == '&')
		{
			(*i)++;
			return (1);
		}
		(*i)--;
		return (0);
	}
	remember_me = s[*i];
	(*i)++;
	if (s[*i] == remember_me)
		(*i)++;
	return (1);
}
