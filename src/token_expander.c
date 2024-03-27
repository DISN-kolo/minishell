/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:41:25 by akozin            #+#    #+#             */
/*   Updated: 2024/03/27 18:08:48 by akozin           ###   ########.fr       */
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
		if (*in_q == 1 && (s[i] == '\'' || s[i] == '"'))
			*in_q = 0;
		else if (!*in_q && (s[i] == '\'' || s[i] == '"'))
			*in_q = 1;
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
		in_q = 1;
	}
	else if (!ft_strchr(sep, s[i++]))
		count++;
	count += ins_val_c_internal(s, sep, &in_q, i);
	return (count);
}

int	inside_dollar_counter(t_data *data, char *t, int i)
{
	int		ret;
	int		start;
	char	*env_v_name;
	char	*env_v_val;

	start = i + 1;
	if (!strchars(&(t[start]), " \t\f\v!@#$%^&*()-=+[]{}\\;:,./?"))
		env_v_name = ft_substr(&(t[start]), 0, ft_strlen(&(t[start])));
	else
		env_v_name = ft_substr(&(t[start]), 0,
				strchars(&(t[start]), " \t\f\v!@#$%^&*()-=+[]{}\\;:,./?")
				- &(t[start]));
	env_v_val = get_env_var_by_name(data, env_v_name); // TODO placeholder. gets the value by key, accounting for envi
	return (inside_val_counter(env_v_val, " \t\f\v"));
}

int	expansion_counter(t_data *data, char *t)
{
	int	ret;
	int	i;
	int	j;
	int	in_q;

	ret = 1;
	i = 0;
	j = 0;
	in_q = 0;
	while (t[i])
	{
		if (in_q && (t[i] == '\'' || t[i] == '"'))
			in_q = 0;
		else if (!in_q && (t[i] == '\'' || t[i] == '"'))
			in_q = 1;
		if (!in_q && t[i] == '$')
			ret += inside_dollar_counter(data, t, i);
		i++;
	}
}

char **token_expander(t_data *data, char *t)
{
	char	**add_argv;

	add_argv = malloc(sizeof (char *) * (expansion_counter(data, t) + 1));
	if !(add_argv)
		return (NULL); // TODO ?
}
