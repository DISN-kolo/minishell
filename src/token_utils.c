/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:59:08 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/08 12:34:16 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*strchars(char *s, char *sep)
{
	int		in_q;

	in_q = 0;
	while (*s)
	{
		if ((in_q == 1 && *s == '\'') || (in_q == 2 && *s == '"'))
			in_q = 0;
		else if (!in_q && (*s == '\'' || *s == '"'))
			in_q = (*s == '"') + 1;
		if (!in_q && (ft_strchr(sep, *s) || (*s == '&' && *(s + 1) == '&')))
			return (s);
		s++;
	}
	return (NULL);
}

t_tok_s	determine_type(char *t)
{
	if (!ft_strncmp(t, "|", 2))
		return (PIPE);
	if (!ft_strncmp(t, "<", 2) || !ft_strncmp(t, ">", 2)
		|| !ft_strncmp(t, ">>", 3))
		return (REDIR);
	if (!ft_strncmp(t, "<<", 3))
		return (HDOC);
	if (!ft_strncmp(t, "&&", 3))
		return (AND);
	if (!ft_strncmp(t, "||", 3))
		return (OR);
	if (!ft_strncmp(t, "(", 2))
		return (O_BRACKET);
	if (!ft_strncmp(t, ")", 2))
		return (C_BRACKET);
	return (TOKEN);
}
