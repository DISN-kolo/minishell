/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:16:20 by akozin            #+#    #+#             */
/*   Updated: 2024/03/20 14:03:55 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * in_q = 0 == not in quotes
 *      = 1 == in ' '
 *      = 2 == in " "
 *
 * ascii (dec) for " is 34
 * ascii (dec) for ' is 39
 */
static int	token_c(char *s, char *sep)
{
	int		i;
	int		in_q;
	int		count;

	i = -1;
	in_q = 0;
	count = 0;
	if (!s[i + 1])
		return (0);
	if (s[i + 1] == '\'' || s[i + 1] == '"')
		in_q = (s[i + 1] == '"') + 1;
	if (!ft_strchr(sep, s[i++ + 1]))
		count++;
	while (s[i++])
	{
		if (in_q && s[i] == ('"' + 5 * (in_q == 1)))
			in_q = 0;
		else if (!in_q && !ft_strchr(sep, s[i]) && ft_strchr(sep, s[i - 1]))
		{
			count++;
			if (s[i] == '\'' || s[i] == '"')
				in_q = (s[i] == '"') + 1;
		}
	}
	return (count);
}

char	*strchars(char *s, char *sep)
{
	while (*s)
	{
		if (ft_strchr(sep, *s))
			return (s);
		s++;
	}
	return (0);
}

char	**t_split(char *str)
{
	char	**ret;
	size_t	wlen;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof (char *) * (token_c(str, " \t\f\v") + 1));
	if (!ret)
		return (0);
	while (*str)
	{
		while (ft_strchr(" \t\f\v", *str) && *str)
			str++;
		if (*str)
		{
			if (!strchars(str, " \t\f\v"))
				wlen = ft_strlen(str);
			else
				wlen = strchars(str, " \t\f\v") - str;
			ret[i++] = ft_substr(str, 0, wlen);
			str += wlen;
		}
	}
	ret[i] = 0;
	return (ret);
}

void	tokenize_line(char *s, t_data *data)
{
	printf("n of 'tokens' is %3d\n", token_c(s, " \t\f\v"));
//	data->tokens = t_split(s);
//	for (int i = 0; data->tokens[i]; i++)
//		printf("'token' number   %3d: %s\n", i, data->tokens[i]);
	if (data->errored)
		return ;
}
