/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:41:25 by akozin            #+#    #+#             */
/*   Updated: 2024/05/20 14:46:24 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	inside_dollar_counter(t_data *data, char *t, int i)
{
	int		ret;
	char	*env_v_name;
	char	*env_v_val;

	if (t[i] == '~')
		env_v_name = ft_strdup("HOME");
	else
	{
		if (t[i + 1] != '_' && !ft_isalpha(t[i + 1]) && t[i + 1] != '?')
			return (0);
		env_v_name = ft_substr(&t[i + 1], 0, var_end(&t[i + 1]) - &t[i + 1]);
	}
	env_v_val = read_env(data, env_v_name);
	if (!env_v_val)
	{
		ret = ft_strlen(env_v_name);
		return (free(env_v_name), -ret);
	}
	if (t[i] == '~')
		ret = ft_strlen(env_v_val);
	else
		ret = ft_strlen(env_v_val) - ft_strlen(env_v_name);
	free(env_v_val);
	free(env_v_name);
	return (ret);
}

static int	expansion_counter(t_data *data, char *t)
{
	int	ret;
	int	i;
	int	in_q;

	ret = 0;
	i = 0;
	in_q = 0;
	while (t[i])
	{
		determine_q(&in_q, t[i]);
		if ((in_q != 1 && t[i] == '$' && (t[i + 1] == '_' || t[i + 1] == '?'
					|| ft_isalpha(t[i + 1]))) || (t[i] == '~' && !i
				&& ft_strchr(" \t\f\v/", t[1])))
			ret += inside_dollar_counter(data, t, i) - 1;
		i++;
	}
	return (i + ret);
}

static int	exp_t_init(t_token *exp_t, t_data *data, char *c_t, t_tok_s prev)
{
	int	exp_len;

	if (prev == HDOC)
		exp_len = ft_strlen(c_t);
	else
		exp_len = expansion_counter(data, c_t);
	exp_t->token = malloc(exp_len + 1);
	if (!exp_t->token)
		return (1);
	exp_t->literal = malloc(sizeof (int) * exp_len);
	if (!exp_t->literal)
		return (free(exp_t->token), exp_t->token = NULL, 1);
	return (0);
}

/*
 * new tokens = final returned tokens re-made from data->tokens with
 * expansion n stuff
 *
 * local n tokens = tokens received while expanding an existing token from
 * data->tokens. they need to be added to the new tokens
 *
 * exp t is a single token to be expanded. inside of it we push our stuff from
 * the current data->tokens token, then we pass this exp t to the function that
 * creates the local n tokens, dissecting exp t.
 */
t_token	*token_expander(t_data *data, t_token *c_toks)
{
	int		i;
	t_token	*new_tokens;
	t_token	*local_n_t;
	t_token	exp_t;
	int		retval;

	if (init_te_data_linesave(&i, &new_tokens, data, &exp_t))
		return (NULL);
	while (c_toks[++i].token)
	{
		if (exp_t_init(&exp_t, data, c_toks[i].token, nt_prev(new_tokens)))
			return (NULL);
		retval = dollar_exp_helper(&exp_t, data, c_toks, i);
		if (retval == 1)
			return (NULL);
		else if (retval == 2)
			new_tokens[tokenslen(new_tokens) - 1].type = REDIR_AMB;
		local_n_t = new_t_split(&exp_t);
		if (!local_n_t)
			return (NULL);
		new_tokens = tokens_join_free(new_tokens, local_n_t);
		if (!new_tokens)
			return (NULL);
	}
	return (new_tokens);
}
