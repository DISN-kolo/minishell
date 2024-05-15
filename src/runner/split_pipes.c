/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:31:17 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/15 16:21:29 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	pipes_len(t_token *tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i].token)
	{
		if (tokens[i].type == PIPE)
			count++;
		i++;
	}
	return (count + 1);
}

static int	tokens_pipes_len(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token && tokens[i].type != PIPE)
		i++;
	return (i);
}

static t_token	*fill_tokens(t_token *tokens, int len)
{
	t_token	*new_tokens;
	int		i;

	new_tokens = malloc((len + 1) * sizeof (t_token));
	if (!new_tokens)
		return (NULL);
	new_tokens[len].token = NULL;
	i = -1;
	while (++i < len)
	{
		new_tokens[i].token = ft_strdup(tokens[i].token); //TODO CHECK
		new_tokens[i].literal = tokens[i].literal;
		new_tokens[i].type = tokens[i].type;
	}
	return (new_tokens);
}

static void	free_split_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i]);
	free(tokens);
}

t_token	**split_pipes(t_token *tokens)

{
	t_token	**split_tokens;
	int		len;
	int		i;
	int		j;

	len = pipes_len(tokens);
	split_tokens = malloc((len + 1) * sizeof (t_token *));
	if (!split_tokens)
		return (NULL);
	split_tokens[len] = NULL;
	i = 0;
	j = 0;
	while (tokens[i].token)
	{
		len = tokens_pipes_len(tokens + i);
		split_tokens[j] = fill_tokens(tokens + i, len);
		if (!split_tokens[j++])
			return (free_split_tokens(split_tokens), NULL);
		i += len;
		if (tokens[i].type == PIPE)
			i++;
	}
	return (split_tokens);
}
