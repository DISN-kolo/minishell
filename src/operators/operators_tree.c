/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:20:47 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/10 12:56:43 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	tokens_len(t_token *tokens)
{
	int	i;
	int	brackets;

	i = 0;
	brackets = 0;
	while (tokens[i].token)
	{
		if (!brackets && (tokens[i].type == AND || tokens[i].type == OR))
			break ;
		if (tokens[i].type == O_BRACKET)
			brackets++;
		if (tokens[i].type == C_BRACKET)
			brackets--;
		i++;
	}
	return (i);
}

static int	tokens_list_len(t_token *tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i].token)
	{
		i += tokens_len(tokens + i);
		if (tokens[i].type == AND || tokens[i].type == OR)
			i++;
		count++;
	}
	return (count * 2 - 1);
}

static t_token	*tokens_list(t_token *tokens, int len)
{
	t_token	*new_tokens;
	int		i;

	new_tokens = malloc((len + 1) * sizeof (t_token));
	if (!new_tokens)
		return (NULL);
	new_tokens[len].token = NULL;
	i = 0;
	while (i < len)
	{
		new_tokens[i].token = tokens[i].token;
		new_tokens[i].literal = tokens[i].literal;
		new_tokens[i].type = tokens[i].type;
		i++;
	}
	return (new_tokens);
}

t_token **create_tokens_list(t_token *tokens)
{
	t_token	**token_list;
	int		len;
	int		i[3];

	len = tokens_list_len(tokens);
	token_list = malloc((len + 1) * sizeof (t_token *));
	if (!token_list)
		return (NULL);
	token_list[len] = NULL;
	i[0] = -1;
	i[1] = 0;
	while (++i[0] < len)
	{
		i[2] = tokens_len(tokens + i[1]);
		token_list[i[0]] = tokens_list(tokens + i[1], i[2]);
		if (!token_list[i[0]])
			return (free_tokens_list(token_list), NULL);
		i[1] += i[2];
		if (tokens[i[1]].type == AND || tokens[i[1]].type == OR)
			token_list[++i[0]] = tokens_list(tokens + i[1]++, 1);
		if (!token_list[i[0]])
			return (free_tokens_list(token_list), NULL);
	}
	return (token_list);
}
