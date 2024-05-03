/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:06:47 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/02 23:27:50 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	tokens_len(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token && (tokens[i].type != AND || tokens[i].type != OR))
		i++;
	return (i);
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

static t_cmdtree	*tree_tokens(t_token *tokens, int i)
{
	t_token		*new_tokens;
	t_cmdtree	*tree;

	new_tokens = tokens_list(tokens, i);
	if (!new_tokens)
		return (NULL);
	tree = cmdtree_create(new_tokens);
	return (tree);
}

void	operators_tree(t_data *data)
{
	t_cmdtree	*tree;
	t_token		*tmp_tokens;
	int			i;
	int			count;

	i = 0;
	while (data->tokens[i].token)
	{
		count = tokens_len(data->tokens + i);
		tree = tree_tokens(data->tokens + i + count, 1);
		if (!tree)
			return ; // TODO
		if (!i)
			data->cmds = tree;
		tree->left = tree_tokens(data->tokens + i, count);
		tree->right = 
	}
}
