/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:30:35 by akozin            #+#    #+#             */
/*   Updated: 2024/04/02 12:40:25 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * k is basically var's value len.
 */
void	fill_lit_expanded(int k, t_token *f_me, int in_q, int j)
{
	while (k-- > 0)
	{
		f_me->literal[j - k] = in_q
			|| !ft_strchr(" \t\f\v", f_me->token[j - k]);
	}
}
