/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:48:08 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/28 16:48:09 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	valid_operator(char *s, int *i)
{
	char	remember_me;

	if (s[*i] == '&')
	{
		(*i)++;
		if (s[*i] == '&')
		{
			(*i)++;
			return (1);
		}
		(*i)--;
		return (0);
	}
	remember_me = s[*i];
	(*i)++;
	if (s[*i] == remember_me)
		(*i)++;
	return (1);
}

static int	tokenize_count_loop_else(char *s, char *sep, int *in_q, int i)
{
	int	count;

	count = 0;
	if ((!*in_q && !ft_strchr(sep, s[i]) && s[i] != '\''
			&& s[i] != '"') || (*in_q == 1 && s[i] == '\'')
		|| (*in_q == 2 && s[i] == '"'))
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
	return (count);
}

static int	tokenize_count_loop(char *s, char *sep, int *in_q, int i)
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
			count += tokenize_count_loop_else(s, sep, in_q, i);
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
int	tokenize_count(char *s, char *sep)
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
		in_q = 1 + (s[i - 1] == '"');
	}
	else if (ft_strchr("|&<>", s[i]) && valid_operator(s, &i))
		count++;
	else if (!ft_strchr(sep, s[i++]))
		count++;
	count += tokenize_count_loop(s, sep, &in_q, i);
	if (!in_q)
		return (count);
	return (-2);
}
