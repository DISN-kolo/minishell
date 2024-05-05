/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:20:47 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/05 18:39:50 by molasz-a         ###   ########.fr       */
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

static t_token	*tokens_list(t_token *tokens, int len)
{
	t_token	*new_tokens;
	int		i;

	if (tokens[0].type == O_BRACKET && tokens[len - 1].type == C_BRACKET)
	{
		tokens++;
		len -= 2;
	}
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

static	t_cmdtree	*tree_recurs(t_token *tokens) // TODO check leaks
{
	t_cmdtree	*tree;
	t_token		*new_tokens;
	int			i;

	i = tokens_len(tokens);
	tree = cmdtree_create(NULL);
	new_tokens = tokens_list(tokens, i);
	if (!tree || !new_tokens)
		return (NULL);
	if (tokens[i].token)
	{
		tree->left = tree_recurs(new_tokens);
		tree->tokens = tokens_list(tokens + i, 1);
		tree->right = tree_recurs(tokens + i + 1);
	}
	else if (tokens[0].type == O_BRACKET && tokens[i - 1].type == C_BRACKET)
		tree = tree_recurs(new_tokens);
	else
		tree->tokens = new_tokens;
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

	printf("TREE:");
	i = 0;
	while (tokens[i].token)
	{
		printf("%s (%d) ", tokens[i].token, tokens[i].type);
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
