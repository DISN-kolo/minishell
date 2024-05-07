/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:10:50 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/07 17:37:04 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_double(char **p)
{
	int	i;

	if (!p)
		return ;
	i = 0;
	while (p[i])
	{
		free(p[i]);
		p[i++] = NULL;
	}
	free(p);
	p = NULL;
}

void	free_tokens(t_token *tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].token)
	{
		free(tokens[i].token);
		if (tokens[i].literal)
			free(tokens[i].literal);
		i++;
	}
	free(tokens);
}

void	free_coms(t_com *coms)
{
	int	i;

	if (!coms)
		return ;
	i = 0;
	while (coms[i].com)
		free_double(coms[i++].com);
	free(coms);
}

void	free_tree(t_cmdtree *tree)
{
	if (tree)
	{
		free_tree(tree->right);
		free_tree(tree->left);
		free(tree);
	}
}

void	data_cleaner(t_data *data)
{
	free_tokens(data->tokens);
	data->tokens = NULL;
	free_coms(data->coms);
	data->coms = NULL;
	free_tree(data->cmdtree);
	data->cmdtree = NULL;
	data->errored = 0;
}

void	free_env(t_env *env)
{
	int	i;

	if (!env)
		return ;
	i = -1;
	while (env[++i].key && env[i].value)
	{
		if (env[i].key)
			free(env[i].key);
		if (env[i].value)
			free(env[i].value);
	}
	free(env);
}
