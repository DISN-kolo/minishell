/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:33:07 by akozin            #+#    #+#             */
/*   Updated: 2024/04/05 13:58:08 by akozin           ###   ########.fr       */
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
	printf("is the first char literal? %d\n", t.literal[i]);
	if ((t.token[i] == '\'' || t.token[i] == '"') && !t.literal[i])
	{
		count++;
		in_q = 1 + (t.token[i] == '"');
	}
	else if (t.literal[i])
		count++;
	count += new_t_c_internal(t, " \t\f\v", &in_q, i);
	if (!in_q)
		return (printf("we've counted %d tokens here\n", count), count);
	return (-2);
}

char	*strchars_lit(t_token *t, int k, char *sep)
{
	int		in_q;

	in_q = 0;
	while (t->token[k])
	{
		if (!t->literal[k])
		{
			if ((in_q == 1 && t->token[k] == '\'')
					|| (in_q == 2 && t->token[k] == '"'))
				in_q = 0;
			else if (!in_q && (t->token[k] == '\'' || t->token[k] == '"'))
				in_q = (t->token[k] == '"') + 1;
		}
		if (!in_q && ft_strchr(sep, t->token[k]) && !t->literal[k])
			return (&(t->token[k]));
		k++;
	}
	return (NULL);
}

static int	new_t_split_internal(t_token *t, int *k, t_token **ret, int *i)
{
	size_t	wlen;

	if (!strchars_lit(t, *k, " \t\f\v"))
		wlen = ft_strlen(&(t->token[*k]));
	else
		wlen = strchars_lit(t, *k, " \t\f\v") - &(t->token[*k]);
	ret[*i]->token = ft_substr(&(t->token[*k]), 0, wlen);
	if (!ret[*i]->token)
//		return (free_ret(ret), 1); // TODO huh?
		return (1);
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
