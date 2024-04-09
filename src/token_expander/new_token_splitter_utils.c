/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_splitter_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:42:35 by akozin            #+#    #+#             */
/*   Updated: 2024/04/09 13:49:54 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*strchars_lit(t_token *t, int k, char *sep)
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
			return (&(t->token[k]));
		k++;
	}
	return (NULL);
}
