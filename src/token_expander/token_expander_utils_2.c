/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:11 by akozin            #+#    #+#             */
/*   Updated: 2024/05/08 12:02:04 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dollar_exp_helper(t_token *exp_t, t_data *data, t_token *c_toks, int i)
{
	int	r;

	// c_toks[i].type = determine_type(c_toks[i].token); MOVED TO tokenize_line
	if (i > 0)
		r = dollar_expander(exp_t, data, c_toks[i].token, c_toks[i - 1].type);
	else
		r = dollar_expander(exp_t, data, c_toks[i].token, TOKEN);
	if (c_toks[i].type == TOKEN && i > 0 && r == 2 && data->amb_tok_ind == -42)
	{
		printf("amb redir marked\n");
		data->amb_tok_name = c_toks[i].token;
		data->amb_tok_ind = i;
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

int	init_te_data_linesave(int *i, t_token **new_tokens, t_data *data)
{
	data->amb_tok_ind = -42;
	data->amb_tok_name = NULL;
	*i = 0;
	*new_tokens = NULL;
	return (0);
}
