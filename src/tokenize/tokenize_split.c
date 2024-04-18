/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:48:14 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/16 11:05:54 by akozin           ###   ########.fr       */
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

static int	tokenize_split_strs(char **str, t_token **ret, int *i)
{
	size_t	wlen;

	if (ft_strchr("<>|", **str) || (**str == '&' && *(*str + 1) == '&'))
	{
		if (**str == *(*str + 1))
			wlen = 2;
		else
			wlen = 1;
	}
	else
	{
		if (!strchars(*str, " \t\f\v<>|"))
			wlen = ft_strlen(*str);
		else
			wlen = strchars(*str, " \t\f\v<>|") - *str;
	}
	(*ret)[*i].token = ft_substr(*str, 0, wlen);
	if (!(*ret)[*i].token)
		return (free_ret(ret));
	(*i)++;
	*str += wlen;
	return (0);
}

t_token	*tokenize_split(char *str)
{
	t_token	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof (t_token) * (tokenize_count(str, " \t\f\v") + 1));
	if (!ret)
		return (NULL);
	while (*str)
	{
		while (ft_strchr(" \t\f\v", *str) && *str)
			str++;
		if (*str)
		{
			if (tokenize_split_strs(&str, &ret, &i))
				return (NULL);
		}
	}
	ret[i].token = NULL;
	return (ret);
}
