/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:55:23 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/02 22:00:43 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmdtree	*cmdtree_create(t_token *tokens)
{
	t_cmdtree	*tree;

	tree = malloc(sizeof(t_cmdtree));
	if (!tree)
		return (NULL);
	tree->tokens = tokens;
	tree->left = 0;
	tree->right = 0;
	return (tree);
}
