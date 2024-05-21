/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_err_probe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:50:11 by akozin            #+#    #+#             */
/*   Updated: 2024/05/21 11:58:37 by akozin           ###   ########.fr       */
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
		|| (probe_ops(tokens[i].type) && probe_ops(tokens[i - 1].type)))
		return (1);
	return (0);
}

int	tokenize_err_probe(t_data *data, t_token *tokens)
{
	int	i;

	if (!tokens || !tokens[0].token)
		return (0);
	if (probe_ops(tokens[0].type))
	{
		data->sp_hdoc = 0;
		return (1);
	}
	i = 1;
	while (tokens[i].token)
	{
		if (probe_all(tokens, i))
		{
			data->sp_hdoc = i;
			return (1);
		}
		i++;
	}
	if (probe_redirs(tokens[i - 1].type) || probe_ops(tokens[i - 1].type))
	{
		data->sp_hdoc = i - 1;
		return (1);
	}
	return (0);
}
