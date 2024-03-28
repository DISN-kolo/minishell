/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_probe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:50:11 by akozin            #+#    #+#             */
/*   Updated: 2024/03/28 15:43:04 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	probe_all(t_token *tokens, int i)
{
	if (!ft_strncmp(tokens[i].token, "|", 2)
		|| !ft_strncmp(tokens[i].token, "||", 3)
		|| !ft_strncmp(tokens[i].token, "&&", 3)
		|| !ft_strncmp(tokens[i].token, "<", 2)
		|| !ft_strncmp(tokens[i].token, "<<", 3)
		|| !ft_strncmp(tokens[i].token, ">", 2)
		|| !ft_strncmp(tokens[i].token, ">>", 3))
		return (1);
	return (0);
}

int	probe_redirs(t_token *tokens, int i)
{
	if (!ft_strncmp(tokens[i].token, "<", 2)
		|| !ft_strncmp(tokens[i].token, "<<", 3)
		|| !ft_strncmp(tokens[i].token, ">", 2)
		|| !ft_strncmp(tokens[i].token, ">>", 3))
		return (1);
	return (0);
}

int	probe_ops(t_token *tokens, int i)
{
	if (!ft_strncmp(tokens[i].token, "|", 2)
		|| !ft_strncmp(tokens[i].token, "||", 3)
		|| !ft_strncmp(tokens[i].token, "&&", 3))
		return (1);
	return (0);
}

int	last_probe(t_token *tokens, int i)
{
	if (probe_all(tokens, i - 1))
		return (tokenize_error(tokens[i - 1], i - 1));
	return (0);
}

int	t_err_probe(t_token *tokens)
{
	int	i;

	i = 0;
	if (!tokens[0].token)
		return (0);
	if (!ft_strncmp(tokens[0].token, "|", 2)
		|| !ft_strncmp(tokens[0].token, "||", 3)
		|| !ft_strncmp(tokens[0].token, "&&", 3))
		return (tokenize_error(tokens[0], 0));
	i++;
	while (tokens[i].token)
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
