/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:20:47 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/03 14:26:17 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	tokens_len(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token && tokens[i].type != AND && tokens[i].type != OR)
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

static	t_cmdtree	*tree_recurs(t_token *tokens)
{
	t_cmdtree	*tree;
	int	i;

	tree = cmdtree_create(NULL);
	if (!tree)
		return (NULL);
	i = tokens_len(tokens);
	if (!tokens[i].token)
		tree->tokens = tokens_list(tokens, i);
	else
	{
		tree->left = tree_recurs(tokens_list(tokens, i));
		tree->tokens = tokens_list(tokens + i, 1);
		tree->right = tree_recurs(tokens + i + 1);
	}
	return (tree);
}

static void	btree_apply_infix(t_cmdtree *root, void applyf(t_token *))
{
	if (root)
	{
		btree_apply_infix(root->left, applyf);
		applyf(root->tokens);
		btree_apply_infix(root->right, applyf);
	}
}

static	void	on_print(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token)
	{
		printf("%s, ", tokens[i].token);
		i++;
	}
	printf("\n");
}

int	operators_tree(t_data *data)
{
	t_cmdtree	*tree;

	tree = tree_recurs(data->tokens);
	if (!tree)
		return (1);
	btree_apply_infix(tree, on_print);
	return (0);
}
