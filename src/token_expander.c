/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:41:25 by akozin            #+#    #+#             */
/*   Updated: 2024/03/28 12:29:48 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * LITERALLY tokenizer count logic, but without the <>|& stuff
 * lol it's actually quite a lot more simple
 */
int	ins_val_c_internal(char *s, char *sep, int *in_q, int i)
{
	int	count;

	count = 0;
	while (s[i])
	{
		if ((*in_q == 1 && s[i] == '\'') || (*in_q == 2 && s[i] == '"'))
			*in_q = 0;
		else if (!*in_q && (s[i] == '\'' || s[i] == '"'))
			*in_q = (s[i] == '"') + 1;
		if ((!*in_q && !ft_strchr(sep, s[i]) && s[i] != '\''
				&& s[i] != '"') || (*in_q == 1 && s[i] == '\'')
			|| (*in_q == 2 && s[i] == '"'))
		{
			if (ft_strchr(sep, s[i - 1]))
				count++;
		}
		i++;
	}
	return (count);
}

int	inside_val_counter(char *s, char *sep)
{
	int		i;
	int		in_q;
	int		count;

	i = 0;
	in_q = 0;
	count = 0;
	if (!s[i])
		return (0);
	if (s[i] == '\'' || s[i] == '"')
	{
		i++;
		count++;
		in_q = 1 + (s[i - 1] == '"');
	}
	else if (!ft_strchr(sep, s[i++]))
		count++;
	count += ins_val_c_internal(s, sep, &in_q, i);
	return (count);
}

int	inside_dollar_counter(t_data *data, char *t, int i)
{
	int		ret;
	char	*env_v_name;
	char	*env_v_val;

	if (t[i + 1] != '_' && !ft_isalpha(t[i + 1]))
		return (0);
	env_v_name = ft_substr(&t[i + 1], 0, var_end(&t[i + 1]) - &t[i + 1]);
	env_v_val = get_env_var_by_name(data, env_v_name); // TODO placeholder. gets the value by key, accounting for envi
	ret = ft_strlen(env_v_val) - ft_strlen(env_v_name);
	free(env_v_name);
	free(env_v_val);
	return (ret);
}

int	expansion_counter(t_data *data, char *t)
{
	int	ret;
	int	temp_c;
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
		{
			ret += inside_dollar_counter(data, t, i) - 1;
		}
		i++;
	}
	return (i + ret);
}

char **token_expander(t_data *data, char *t)
{
	char	**new_tokens;
	char	*expanded_token;

	expanded_token = malloc(expansion_counter(data, t));
	if !(expanded_token)
		return (NULL); // TODO ?
	new_tokens = malloc(sizeof (char *) * (expansion_counter(data, t) + 1));
	if !(add_argv)
		return (NULL); // TODO ?
}
