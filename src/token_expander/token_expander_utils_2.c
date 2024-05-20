/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:11 by akozin            #+#    #+#             */
/*   Updated: 2024/05/20 17:03:40 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dollar_exp_helper(t_token *exp_t, t_data *data, t_token *c_toks, int i)
{
	int	r;

	if (i > 0)
		r = dollar_expander(exp_t, data, c_toks[i].token, c_toks[i - 1].type);
	else
		r = dollar_expander(exp_t, data, c_toks[i].token, TOKEN);
	if (c_toks[i].type == TOKEN && i > 0 && r == 2 && data->amb_tok_ind == -42)
	{
		data->amb_tok_name = c_toks[i].token;
		data->amb_tok_ind = i;
		print_error(NULL, data->amb_tok_name, "ambiguous redirect");
	}
	return (r);
}

/*
 * if an expanded token, before its re-splitting, is empty or has un-literal
 * spaces, this means that it's unsuitable for a redirect.
 * this goes to dolalr_expander.
 */
int	unlit_spaces_probe(t_token *f_me)
{
	int	i;

	i = 0;
	if (!f_me->token[0])
		return (2);
	while (f_me->token[i])
	{
		if (ft_strchr(" \t\f\v", f_me->token[i]) && !f_me->literal[i])
			return (2);
		i++;
	}
	return (0);
}

t_tok_s	nt_prev(t_token *new_tokens)
{
	int		i;
	t_tok_s	ret;

	if (!new_tokens)
		return (TOKEN);
	else
	{
		i = 0;
		ret = TOKEN;
		while (new_tokens[i].token)
		{
			ret = new_tokens[i].type;
			i++;
		}
	}
	return (ret);
}

int	init_te_data_linesave(int *i, t_token **new_tokens, t_data *data,
	t_token *exp_t)
{
	data->amb_tok_ind = -42;
	data->amb_tok_name = NULL;
	*i = -1;
	*new_tokens = NULL;
	exp_t->literal = NULL;
	return (0);
}
