/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:16:20 by akozin            #+#    #+#             */
/*   Updated: 2024/03/20 13:25:34 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	token_c(char *s, char *sep)
{
	int		i;
	int		in_quotes;
	int		count;

	i = 0;
	in_quotes = 0;
	count = 0;
	if (!s[i])
		return (0);
	if (!ft_strchr(sep, s[i++]))
		count++;
	while (s[i])
	{
		if (!ft_strchr(sep, s[i]) && ft_strchr(sep, s[i - 1]))
			count++;
		i++;
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
	char	*sep;

	sep = " \t\f\v";
	i = 0;
	ret = (char **)malloc(sizeof (char *) * (token_c(str, sep) + 1));
	if (!ret)
		return (0);
	while (*str)
	{
		while (ft_strchr(sep, *str) && *str)
			str++;
		if (*str)
		{
			if (!strchars(str, sep))
				wlen = ft_strlen(str);
			else
				wlen = strchars(str, sep) - str;
			ret[i++] = ft_substr(str, 0, wlen);
			str += wlen;
		}
	}
	ret[i] = 0;
	return (ret);
}

void	tokenize_line(char *s, t_data *data)
{
	data->tokens = t_split(s);
	for (int i = 0; data->tokens[i]; i++)
		printf("'token' number %3d: %s\n", i, data->tokens[i]);
	if (data->errored)
		return ;
}
