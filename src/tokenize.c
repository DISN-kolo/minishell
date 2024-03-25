/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:16:20 by akozin            #+#    #+#             */
/*   Updated: 2024/03/25 13:12:55 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/libft.h"

int	token_c_internal(char *s, char *sep, int *in_q, int i)
{
	int	count;

	count = 0;
	while (s[i])
	{
		if ((*in_q == 1 && s[i] == '\'') || (*in_q == 2 && s[i] == '"'))
			*in_q = 0;
		else if (!*in_q && (s[i] == '\'' || s[i] == '"'))
			*in_q = (s[i] == '"') + 1;
		if (!*in_q && (ft_strchr("|<>", s[i]) || (s[i] == '&'
				&& s[i + 1] == '&')) && valid_operator(s, &i))
			count++;
		else
		{
			if ((!*in_q && !ft_strchr(sep, s[i]) && s[i] != '\''
						&& s[i] != '"') || (*in_q && (s[i] == '\''
						|| s[i] == '"')))
			{
				if (i >= 2)
				{
					if (ft_strchr(sep, s[i - 1])
						|| (ft_strchr("|<>", s[i - 1]) || (s[i - 2] == '&'
						&& s[i - 1] == '&')))
						count++;
				}
				else
				{
					if (ft_strchr(sep, s[i - 1])
						|| ft_strchr("|<>", s[i - 1]))
						count++;
				}
			}
			i++;
		}
	}
	return (count);
}

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

	i = 0;
	in_q = 0;
	count = 0;
	if (!s[i])
		return (0);
	if (s[i] == '\'')
	{
		i++;
		count++;
		in_q = 1;
	}
	else if (s[i] == '"')
	{
		i++;
		count++;
		in_q = 2;
	}
	else if (ft_strchr("|&<>", s[i]) && valid_operator(s, &i))
		count++;
	else if (!ft_strchr(sep, s[i++]))
		count++;
	count += token_c_internal(s, sep, &in_q, i);
	if (!in_q)
		return (count);
	return (-2);
}

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
			if (ft_strchr("<>|", *str) || (*str == '&' && *(str + 1) == '&'))
			{
				if (*str == *(str + 1))
					wlen = 2;
				else
					wlen = 1;
			}
			else 
			{
				if (!strchars(str, " \t\f\v<>|"))
					wlen = ft_strlen(str);
				else
					wlen = strchars(str, " \t\f\v<>|") - str;
			}
			ret[i++] = ft_substr(str, 0, wlen);
			//TODO malloc protection
			str += wlen;
		}
	}
	ret[i] = 0;
	return (ret);
}

void	tokenize_line(char *s, t_data *data)
{
	if (data->errored)
		return ;
	printf("n of 'tokens' is %3d\n", token_c(s, " \t\f\v"));
	data->tokens = t_split(s);
	printf("%p\n", data->tokens);
	if (!data->tokens)
		return ;
	for (int i = 0; data->tokens[i]; i++)
		printf("'token' number   %3d: %s\n", i, data->tokens[i]);
}
