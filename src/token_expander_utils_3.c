/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:13:29 by akozin            #+#    #+#             */
/*   Updated: 2024/04/02 16:31:29 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	strchars_lit(t_token *t, int k, char *sep)
{
	int		in_q;

	in_q = 0;
	while (t->token[k])
	{
		if (!t->literal[k])
		{
			if ((in_q == 1 && t->token[k] == '\'')
					|| (in_q == 2 && t->token[k] == '"'))
				in_q = 0;
			else if (!in_q && (t->token[k] == '\'' || t->token[k] == '"'))
				in_q = (t->token[k] == '"') + 1;
		}
		if (!in_q && ft_strchr(sep, t->token[k]) && !t->literal[k])
			return (k);
		k++;
	}
	return (-1);
}

int	tokenslen(t_token *t)
{
	int	ret;

	ret = 0;
	while (t->token)
		ret++;
	return (ret);
}
