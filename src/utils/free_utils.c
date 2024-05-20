/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:10:50 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/20 12:22:20 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	free_token_list(t_token **token_list)
{
	int	i;

	if (!token_list)
		return ;
	i = 0;
	while (token_list[i])
		free(token_list[i++]);
	free(token_list);
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
		free(coms[i].ios);
		free_double(coms[i++].com);
	}
	free(coms);
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
