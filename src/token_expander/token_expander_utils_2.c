/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:11 by akozin            #+#    #+#             */
/*   Updated: 2024/04/17 15:49:06 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	dollar_exp_helper(t_token *exp_t, t_data *data, t_token *c_toks, int i)
{
	c_toks[i].type = determine_type(c_toks[i].token);
	if (i > 0)
		dollar_expander(exp_t, data, c_toks[i].token, c_toks[i - 1].type);
	else
		dollar_expander(exp_t, data, c_toks[i].token, TOKEN);
}
