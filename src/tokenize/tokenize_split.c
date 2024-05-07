/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:48:14 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/07 16:33:29 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	return (0);
}

static int	tokenize_split_strs(char **str, t_token *tokens, int *i)
{
	size_t	wlen;

	if (ft_strchr("<>|()", **str) || (**str == '&' && *(*str + 1) == '&'))
	{
		if (**str != *(*str + 1) || **str == '(' || **str == ')')
			wlen = 1;
		else
			wlen = 2;
	}
	else
	{
		if (!strchars(*str, " \t\f\v<>|()"))
			wlen = ft_strlen(*str);
		else
			wlen = strchars(*str, " \t\f\v<>|()") - *str;
	}
	tokens[*i].token = ft_substr(*str, 0, wlen);
	if (!tokens[*i].token)
		return (free_tokens(tokens), 1);
	(*i)++;
	*str += wlen;
	return (0);
}

static void	init_tokens(t_token *tokens, int len)
{
	int	i;

	i = 0;
	tokens[len].token = NULL;
	while (i < len)
	{
		tokens[i].literal = NULL;
		i++;
	}
}

t_token	*tokenize_split(char *str)
{
	t_token	*tokens;
	int		len;
	int		i;

	i = 0;
	len = tokenize_count(str, " \t\f\v");
	tokens = malloc(sizeof (t_token) * (len + 1));
	if (!tokens)
		return (NULL);
	init_tokens(tokens, len);
	while (*str)
	{
		while (ft_strchr(" \t\f\v", *str) && *str)
			str++;
		if (*str)
		{
			if (tokenize_split_strs(&str, tokens, &i))
				return (NULL);
		}
	}
	return (tokens);
}
