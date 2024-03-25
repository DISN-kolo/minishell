/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:16:20 by akozin            #+#    #+#             */
/*   Updated: 2024/03/25 17:55:55 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			count += t_c_internal_else(s, sep, in_q, i);
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
	if (s[i] == '\'' || s[i] == '"')
	{
		i++;
		count++;
		in_q = 1 + (s[i] == '"');
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
			t_split_internal(&str, &ret, &i);
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
	if (!data->tokens || t_err_probe(data->tokens))
	{
		data->errored = 1;
		return ;
	}
	for (int i = 0; data->tokens[i]; i++)
		printf("'token' number   %3d: %s\n", i, data->tokens[i]);
}
