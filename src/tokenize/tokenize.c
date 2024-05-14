/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:16:20 by akozin            #+#    #+#             */
/*   Updated: 2024/05/09 13:07:52 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static t_token	*tokenize_split(char *str)
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

t_error	tokenize(char *s, t_data *data)
{
	int	i;

	data->tokens = tokenize_split(s);
	if (!data->tokens)
		return (MALLOC_ERR);
	i = -1;
	while (data->tokens[++i].token)
		data->tokens[i].type = determine_type(data->tokens[i].token);
	if (tokenize_err_probe(data, data->tokens))
		return (SYNTAX_ERR);
	return (NULL_ERR);
}
