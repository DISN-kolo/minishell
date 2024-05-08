/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_probe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:50:11 by akozin            #+#    #+#             */
/*   Updated: 2024/05/08 19:27:07 by molasz-a         ###   ########.fr       */
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

static int	probe_brackets(t_tok_s type)
{
	if (type == O_BRACKET || type == C_BRACKET)
		return (1);
	return (0);
}

int tokenize_err_probe(t_token *tokens)
{
	int	i;

	i = 0;
	if (probe_ops(tokens[0].type))
		return (tokenize_error(tokens[0].token), 0);
	i++;
	while (tokens[i].token)
	{
		if (((probe_redirs(tokens[i].type) || probe_ops(tokens[i].type)) && probe_redirs(tokens[i - 1].type))
				|| (probe_ops(tokens[i].type) && probe_ops(tokens[i - 1].type)))
			return (tokenize_error(tokens[i].token), 0);
		i++;
	}
	if (probe_redirs(tokens[i].type) || probe_ops(tokens[i].type))
		return (tokenize_error(tokens[i - 1].token), 0);
	return (0);
}
