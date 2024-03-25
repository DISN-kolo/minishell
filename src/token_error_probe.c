/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_probe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:50:11 by akozin            #+#    #+#             */
/*   Updated: 2024/03/25 17:29:55 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	probe_all(char **tokens, int i)
{
	if (!ft_strncmp(tokens[i], "|", 2) || !ft_strncmp(tokens[i], "||", 3)
		|| !ft_strncmp(tokens[i], "&&", 3) || !ft_strncmp(tokens[i], "<", 2)
		|| !ft_strncmp(tokens[i], "<<", 3) || !ft_strncmp(tokens[i], ">", 2)
		|| !ft_strncmp(tokens[i], ">>", 3))
		return (1);
	return (0);
}

int	probe_redirs(char **tokens, int i)
{
	if (!ft_strncmp(tokens[i], "<", 2) || !ft_strncmp(tokens[i], "<<", 3)
		|| !ft_strncmp(tokens[i], ">", 2) || !ft_strncmp(tokens[i], ">>", 3))
		return (1);
	return (0);
}

int	probe_ops(char **tokens, int i)
{
	if (!ft_strncmp(tokens[i], "|", 2) || !ft_strncmp(tokens[i], "||", 3)
		|| !ft_strncmp(tokens[i], "&&", 3))
		return (1);
	return (0);
}

int	last_probe(char **tokens, int i)
{
	if (probe_all(tokens, i - 1))
		return (tokenize_error(tokens[i - 1], i - 1));
	return (0);
}

int	t_err_probe(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens[0])
		return (0);
	if (!ft_strncmp(tokens[0], "|", 2) || !ft_strncmp(tokens[0], "||", 3)
		|| !ft_strncmp(tokens[0], "&&", 3))
		return (tokenize_error(tokens[0], 0));
	i++;
	while (tokens[i])
	{
		if (probe_all(tokens, i))
		{
			if (probe_redirs(tokens, i - 1))
				return (tokenize_error(tokens[i], i));
		}
		if (probe_ops(tokens, i))
		{
			if (probe_ops(tokens, i - 1))
				return (tokenize_error(tokens[i], i));
		}
		i++;
	}
	return (last_probe(tokens, i));
}
