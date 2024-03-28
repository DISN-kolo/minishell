/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:24:06 by akozin            #+#    #+#             */
/*   Updated: 2024/03/28 15:26:27 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	valid_operator(char *s, int *i)
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

static int	free_ret(t_token **ret)
{
	int	i;

	i = 0;
	while ((*ret)[i])
	{
		if ((*ret)[i].token)
			free((*ret)[i].token);
		free((*ret)[i++]);
	}
	free(*ret);
	return (1);
}

int	t_split_internal(char **str, t_token **ret, int *i)
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

int	t_c_internal_else(char *s, char *sep, int *in_q, int i)
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
