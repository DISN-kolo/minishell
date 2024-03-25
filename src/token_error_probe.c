/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_probe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:50:11 by akozin            #+#    #+#             */
/*   Updated: 2024/03/25 16:55:34 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
int	tokenize_error(char *s, int i)
{
	perror("Incorrect token placement of "s" at position")
}

int	t_err_probe(char **tokens)
{
	int	i;

	i = 0;
	if (!ft_strcmp(tokens[0], "|") || !ft_strcmp(tokens[0], "||")
			|| !ft_strcmp(tokens[0], "&&"))
		return (tokenize_error()); // TODO
	i++;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "|") || !ft_strcmp(tokens[i], "||")
			|| !ft_strcmp(tokens[i], "&&") || !ft_strcmp(tokens[i], "<")
			|| !ft_strcmp(tokens[i], "<<") || !ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], ">>"))
		{
			if (!ft_strcmp(tokens[i - 1], "<")
				|| !ft_strcmp(tokens[i - 1], "<<")
				|| !ft_strcmp(tokens[i - 1], ">")
				|| !ft_strcmp(tokens[i - 1], ">>"))
				return (tokenize_error()); // TODO
		}
		if (!ft_strcmp(tokens[i], "|") || !ft_strcmp(tokens[i], "||")
			|| !ft_strcmp(tokens[i], "&&"))
		{
			if (!ft_strcmp(tokens[i - 1], "|")
				|| !ft_strcmp(tokens[i - 1], "||")
				|| !ft_strcmp(tokens[i - 1], "&&"))
				return (tokenize_error()); // TODO
		}
	}
}
