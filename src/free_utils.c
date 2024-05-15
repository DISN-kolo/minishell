/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:10:50 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/08 16:23:37 by akozin           ###   ########.fr       */
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
	{
		if (coms[i].infd != -42 && close(coms[i].infd) < 0)
			print_perror("Close infd data cleaner", -1);
		if (coms[i].outfd != -42 && close(coms[i].outfd) < 0)
			print_perror("Close outfd data cleaner", -1);
		free_double(coms[i++].com);
	}
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

void	free_heredocs(t_hdoc **heredocs)
{
	int	i;
	int	j;

	if (!heredocs)
		return ;
	i = 0;
	while (heredocs[i])
	{
		j = 0;
		while (heredocs[i][j].str)
			free(heredocs[i][j++].str);
		free(heredocs[i++]);
	}
	free(heredocs);
}

void	data_cleaner(t_data *data)
{
	free_tokens(data->tokens);
	data->tokens = NULL;
	free_heredocs(data->hds);
	data->hds = NULL;
	free_tree(data->cmdtree);
	data->cmdtree = NULL;
	free_coms(data->coms);
	data->coms = NULL;
	data->hd_counter = 0;
	data->status_code = 0;
	data->skip_cmd = 0;
	data->skip_brackets = 0;
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
