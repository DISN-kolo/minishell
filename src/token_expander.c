/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:41:25 by akozin            #+#    #+#             */
/*   Updated: 2024/03/28 15:22:06 by akozin           ###   ########.fr       */
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

static int	fill_expanded_token(char **f_me, t_data *data, char *t)
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
			(*f_me)[j] = t[i];
		i++;
		j++;
	}
	(*f_me)[j] = 0;
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

char **token_expander(t_data *data, char *t)
{
	char	**new_tokens;
	char	*expanded_token;
	int		*expanded_literals;

	expanded_token = malloc(expansion_counter(data, t));
	expanded_literals = malloc(sizeof (int) * expansion_counter(data, t));
	if !(expanded_token)
		return (NULL); // TODO ?
	if (fill_expanded_token(&expanded_token, data, t))
		return (NULL); // TODO errhandling
	new_tokens = malloc(sizeof (char *) * (new_t_counter(data, t) + 1));
	if !(add_argv)
		return (NULL); // TODO ?
}
