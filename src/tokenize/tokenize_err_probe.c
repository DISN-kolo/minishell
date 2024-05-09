/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_probe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:50:11 by akozin            #+#    #+#             */
/*   Updated: 2024/05/09 11:36:36 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	probe_redirs(t_tok_s type)
{
	if (type == REDIR || type == HDOC)
		return (1);
	return (0);
}

static int	probe_ops(t_tok_s type)
{
	if (type == PIPE || type == AND || type == OR)
		return (1);
	return (0);
}

static int	probe_all(t_tok_s type)
{
	if (probe_redirs(type) || probe_ops(type))
		return (1);
	return (0);
}

static int	probe_brackets_level(t_token *tokens)
{
	int	i;
	int	brackets;

	i = 0;
	brackets = 0;
	while (tokens[i].token)
	{
		if (tokens[i].type == O_BRACKET)
			brackets++;
		else if (tokens[i].type == C_BRACKET)
			brackets--;
		if (brackets < 0)
			break ;
		i++;
	}
	if (brackets > 0)
		tokenize_error("(");
	else if (brackets < 0)
		tokenize_error(")");
	return (brackets);
}

int	tokenize_err_probe(t_token *tokens)
{
	int	i;

	i = 0;
	if (probe_brackets_level(tokens))
		return (0);
	if (probe_ops(tokens[0].type))
		return (tokenize_error(tokens[0].token), 0);
	i++;
	while (tokens[i].token)
	{
		if ((probe_all(tokens[i].type) && probe_redirs(tokens[i - 1].type))
			|| (probe_ops(tokens[i].type) && probe_ops(tokens[i - 1].type))
			|| (tokens[i].type == O_BRACKET && !probe_ops(tokens[i - 1].type))
			|| (tokens[i].type == C_BRACKET && (!probe_ops(tokens[i + 1].type)
					&& tokens[i + 1].token))
			|| (tokens[i].type == O_BRACKET && tokens[i + 1].type == C_BRACKET))
			return (tokenize_error(tokens[i].token), 0);
		i++;
	}
	if (probe_all(tokens[i - 1].type))
		return (tokenize_error(tokens[i - 1].token), 0);
	return (0);
}
