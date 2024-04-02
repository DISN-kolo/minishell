/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:41:25 by akozin            #+#    #+#             */
/*   Updated: 2024/04/02 12:37:26 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int fill_token(t_token *f_me, char *t, t_data *data, int *j)
{
	char	*env_v_name;
	char	*env_v_val;
	int		k;

	k = 0;
	env_v_name = ft_substr(t, 0, var_end(t) - t);
	env_v_val = read_env(data, env_v_name); // TODO
	if (!env_v_val)
		return (-1);
	while (env_v_val[k])
	{
		f_me->token[*j] = env_v_val[k];
		k++;
		(*j)++;
	}
	(*j)--;
	free(env_v_name);
	free(env_v_val); // do we free it? can we free it?
	return (k);
}
/* ^ use k to know how many ints to fill in the literals arr
 */

static int	dollar_expander(t_token *f_me, t_data *data, int envi, char *t)
{
	int		i;
	int		j;
	int		in_q;

	i = 0;
	j = 0;
	in_q = 0;
	while (t[i])
	{
		determine_q(&in_q, t[i]);
		if (in_q != 1 && t[i] == '$'
				&& (t[i + 1] == '_' || ft_isalpha(t[i + 1])))
		{
			fill_lit_expanded(fill_token(f_me, &t[i + 1], data, &j), f_me, in_q, j);
			i += var_end(&t[i + 1]) - &t[i + 1];
		}
		else
			f_me->token[j] = t[i];
		literal_filler(in_q, t[i], f_me, j);
		i++;
		j++;
	}
	f_me->token[j] = 0;
}

static int	inside_dollar_counter(t_data *data, int envi, char *t, int i)
{
	int		ret;
	char	*env_v_name;
	char	*env_v_val;

	if (t[i + 1] != '_' && !ft_isalpha(t[i + 1]))
		return (0);
	env_v_name = ft_substr(&t[i + 1], 0, var_end(&t[i + 1]) - &t[i + 1]);
	env_v_val = read_env(data, env_v_name); // TODO envi? madonn
	ret = ft_strlen(env_v_val) - ft_strlen(env_v_name);
	free(env_v_name);
	free(env_v_val);
	return (ret);
}

static int	expansion_counter(t_data *data, int envi, char *t)
{
	int	ret;
	int	i;
	int	in_q;

	ret = 0;
	i = 0;
	in_q = 0;
	while (t[i])
	{
		if ((*in_q == 1 && t[i] == '\'') || (*in_q == 2 && t[i] == '"'))
			*in_q = 0;
		else if (!*in_q && (t[i] == '\'' || t[i] == '"'))
			*in_q = (t[i] == '"') + 1;
		if (in_q != 1 && t[i] == '$')
			ret += inside_dollar_counter(data, envi, t, i) - 1;
		i++;
	}
	return (i + ret);
}

t_token *token_expander(t_data *data, int envi, char *t)
{
	int		i;
	t_token	*new_tokens;
	t_token	*local_n_t;
	t_token	exp_t;

	i = 0;
	while (data->tokens[i].token) // TODO norm, error returns
	{
		exp_t.token = malloc(expansion_counter(data, envi, data->tokens[i].token));
		exp_t.literal = malloc(sizeof (int) * expansion_counter(data, envi, data->tokens[i].token));
		if (!exp_t.token || !exp_t.literal)
			return (NULL);
		dollar_expander(&exp_t, data, envi);
		local_n_t = malloc(sizeof (t_token) * (new_t_c(exp_t) + 1));
		if (!local_n_t)
			return (NULL);
		local_n_t = new_t_split(exp_t); // TODO like an ft_split, but has ", ' and literals in mind
		new_tokens = tokens_join_free(new_tokens, local_n_t);
		if (!new_tokens)
			return (NULL);
		i++;
	}
	free(data->tokens); // TODO free_all or something
	return (new_tokens);
}