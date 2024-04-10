/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:33:07 by akozin            #+#    #+#             */
/*   Updated: 2024/04/10 12:39:05 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	new_t_c_internal(t_token t, char *sep, int *in_q, int i)
{
	int	count;

	i++;
	count = 0;
	while (t.token[i])
	{
		if (!t.literal[i])
		{
			if ((*in_q == 1 && t.token[i] == '\'')
				|| (*in_q == 2 && t.token[i] == '"'))
				*in_q = 0;
			else if (!*in_q && (t.token[i] == '\'' || t.token[i] == '"'))
				*in_q = (t.token[i] == '"') + 1;
		}
		if (!t.literal[i - 1] && ft_strchr(sep, t.token[i - 1])
			&& (t.literal[i] || (*in_q == 1 && t.token[i] == '\'')
				|| (*in_q == 2 && t.token[i] == '"')))
			count++;
		i++;
	}
	return (count);
}

/*
 * remake of token counter
 * since it was a single token, we won't have to worry about || && |
 * but since we had an expansion, we have to worry about t.literal
 * we only account for ", ' and spaces if t.literal == 0
 */
static int	new_t_c(t_token t)
{
	int		i;
	int		in_q;
	int		count;

	i = 0;
	in_q = 0;
	count = 0;
	if (!t.token[i])
		return (0);
	if ((t.token[i] == '\'' || t.token[i] == '"') && !t.literal[i])
	{
		count++;
		in_q = 1 + (t.token[i] == '"');
	}
	else if (t.literal[i])
		count++;
	count += new_t_c_internal(t, " \t\f\v", &in_q, i);
	if (!in_q)
		return (count);
	return (-2);
}

static void	fill_and_remove_q(size_t wlen, t_token *t, int k, t_token *ret_one)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (x < wlen)
	{
		if (ft_strchr("\"'", t->token[k + x]) && !t->literal[k + x])
		{
			x++;
			continue ;
		}
		ret_one->token[y] = t->token[k + x];
		x++;
		y++;
	}
	ret_one->token[y] = 0;
}

static int	new_t_split_internal(t_token *t, int *k, t_token **ret, int *i)
{
	size_t	wlen;

	(*ret)[*i].is_pipe = t->is_pipe;
	if (!strchars_lit(t, *k, " \t\f\v"))
		wlen = ft_strlen(&(t->token[*k]));
	else
		wlen = strchars_lit(t, *k, " \t\f\v") - &(t->token[*k]);
	(*ret)[*i].token = malloc(wlen + 1);
	if (!(*ret)[*i].token)
		return (1); // TODO
	fill_and_remove_q(wlen, t, *k, &((*ret)[*i]));
	(*i)++;
	*k += wlen;
	return (0);
}

t_token	*new_t_split(t_token t)
{
	t_token	*ret;
	int		i;
	int		k;

	i = 0;
	k = 0;
	ret = malloc(sizeof (t_token) * (new_t_c(t) + 1));
	if (!ret)
		return (NULL);
	while (t.token[k])
	{
		while (ft_strchr(" \t\f\v", t.token[k]) && t.token[k] && !t.literal[k])
			k++;
		if (t.token[k])
		{
			if (new_t_split_internal(&t, &k, &ret, &i))
				return (NULL);
		}
	}
	ret[i].token = NULL;
	return (ret);
}
