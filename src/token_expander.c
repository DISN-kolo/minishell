/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:41:25 by akozin            #+#    #+#             */
/*   Updated: 2024/03/28 16:54:40 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * LITERALLY tokenizer count logic, but without the <>|& stuff
 * lol it's actually quite a lot more simple
 */
static void	fill_var(char **f_me, char *t, t_data *data, int *j)
{
	char	*env_v_name;
	char	*env_v_val;
	int		k;

	k = 0;
	env_v_name = ft_substr(t, 0, var_end(t) - t);
	env_v_val = read_env(data, env_v_name);
	if (!env_v_val)
		return ;
	while (env_v_val[k])
	{
		(*f_me)[*j] = env_v_val[k];
		k++;
		(*j)++;
	}
	(*j)--;
	free(env_v_name);
	free(env_v_val);
}
/* ^^^ being re-made
 */

static int	token_expander(char *f_me, chart_data *data, char *t)
{
	int		i;
	int		j;
	int		in_q;

	i = 0;
	j = 0;
	in_q = 0;
	while (t[i])
	{
		if ((*in_q == 1 && t[i] == '\'') || (*in_q == 2 && t[i] == '"'))
			*in_q = 0;
		else if (!*in_q && (t[i] == '\'' || t[i] == '"'))
			*in_q = (t[i] == '"') + 1;
		if (in_q != 1 && t[i] == '$'
				&& (t[i + 1] == '_' || ft_isalpha(t[i + 1])))
		{
			fill_var(f_me, &t[i + 1], data, &j);
			i += var_end(&t[i + 1]) - &t[i + 1];
		}
		else
			f_me[j] = t[i];
		i++;
		j++;
	}
	f_me[j] = 0;
}
/* ^^^ being re-made
 */

static int	inside_dollar_counter(t_data *data, char *t, int i)
{
	int		ret;
	char	*env_v_name;
	char	*env_v_val;

	if (t[i + 1] != '_' && !ft_isalpha(t[i + 1]))
		return (0);
	env_v_name = ft_substr(&t[i + 1], 0, var_end(&t[i + 1]) - &t[i + 1]);
	env_v_val = read_env(data, env_v_name);
	ret = ft_strlen(env_v_val) - ft_strlen(env_v_name);
	free(env_v_name);
	free(env_v_val);
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
		if ((*in_q == 1 && t[i] == '\'') || (*in_q == 2 && t[i] == '"'))
			*in_q = 0;
		else if (!*in_q && (t[i] == '\'' || t[i] == '"'))
			*in_q = (t[i] == '"') + 1;
		if (in_q != 1 && t[i] == '$')
			ret += inside_dollar_counter(data, t, i) - 1;
		i++;
	}
	return (i + ret);
}

t_token *token_expander(t_data *data, char *t, int envi)
{
	int		i;
	t_token	*new_tokens;
	t_token	*local_n_t;
	char	*exp_t;
	int		*exp_l;

	i = 0;
	while (data->tokens[i].token) // TODO norm, returns
	{
		exp_t = malloc(expansion_counter(data, envi, t));
		if !(expanded_token)
			return (NULL);
		exp_l = malloc(sizeof (int) * expansion_counter(data, envi, t));
		if !(expanded_literals)
			return (NULL);
		token_expander(exp_t, exp_l, data, envi);
		local_n_t = malloc(sizeof (t_token) * (new_t_c(exp_t, exp_l) + 1));
		if (!local_n_t)
			return (NULL);
		local_n_t = new_t_split(exp_t, exp_l);
		new_tokens = tokens_join_free(new_tokens, local_n_t);
		if (!new_tokens)
			return (NULL);
		i++;
	}
	free(data->tokens); // TODO free_ret or something
	return (new_tokens);
}
