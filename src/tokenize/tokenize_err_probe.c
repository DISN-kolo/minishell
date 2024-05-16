/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_err_probe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:50:11 by akozin            #+#    #+#             */
/*   Updated: 2024/05/16 12:44:02 by akozin           ###   ########.fr       */
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

static int	probe_all(t_token *tokens, int i)
{
	if (((probe_redirs(tokens[i].type) || probe_ops(tokens[i].type))
			&& probe_redirs(tokens[i - 1].type))
		|| (probe_ops(tokens[i].type) && probe_ops(tokens[i - 1].type))
		|| (tokens[i].type == O_BRACKET && !probe_ops(tokens[i - 1].type))
		|| (tokens[i].type == C_BRACKET && (!probe_ops(tokens[i + 1].type)
				&& tokens[i + 1].token))
		|| (tokens[i].type == O_BRACKET && tokens[i + 1].type == C_BRACKET))
		return (tokenize_error(tokens[i].token), 1);
	return (0);
}

static int	probe_brackets_level(t_data *data, t_token *tokens)
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
	if (brackets)
		data->stop_hdoc = i;
	return (brackets);
}

int	tokenize_err_probe(t_data *data, t_token *tokens)
{
	int	i;

	if (!tokens || !tokens[0].token)
		return (0);
	if (probe_brackets_level(data, tokens))
		return (1);
	if (probe_ops(tokens[0].type))
	{
		data->stop_hdoc = 0;
		return (tokenize_error(tokens[0].token), 1);
	}
	i = 1;
	while (tokens[i].token)
	{
		if (probe_all(tokens, i))
			return (data->stop_hdoc = i, 1);
		i++;
	}
	if (probe_redirs(tokens[i - 1].type) || probe_ops(tokens[i - 1].type))
	{
		data->stop_hdoc = i - 1;
		return (tokenize_error(tokens[i - 1].token), 1);
	}
	return (0);
}
