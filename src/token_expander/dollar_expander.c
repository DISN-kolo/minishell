/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:26:06 by akozin            #+#    #+#             */
/*   Updated: 2024/05/20 15:08:36 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	fill_token(t_token *f_me, char *t, t_data *data, int *j)
{
	char	*env_v_name;
	char	*env_v_val;
	int		k;

	k = 0;
	if (*(t - 1) == '~')
		env_v_name = ft_strdup("HOME");
	else
		env_v_name = ft_substr(t, 0, var_end(t) - t);
	if (!env_v_name)
		return (-1);
	env_v_val = read_env(data, env_v_name);
	if (!env_v_val)
		return (free(env_v_name), (*j)--, 0);
	while (env_v_val[k])
	{
		f_me->token[*j] = env_v_val[k];
		k++;
		(*j)++;
	}
	f_me->token[*j] = '\0';
	(*j)--;
	free(env_v_name);
	free(env_v_val);
	return (k);
}
/* ^ use k to know how many ints to fill in the literals arr
 */

void	determine_q(int *in_q, char c)
{
	if ((*in_q == 1 && c == '\'') || (*in_q == 2 && c == '"'))
		*in_q = 0;
	else if (!*in_q && (c == '\'' || c == '"'))
		*in_q = (c == '"') + 1;
}

static int	f_l_exp(int k, t_token *f_me, int in_q, int *j)
{
	if (k < 0)
		return (1);
	while (k-- > 0)
	{
		printf("DOLLAR: %d %d %s\n", *j, k, f_me->token);
		f_me->literal[*j - k] = in_q
			|| !ft_strchr(" \t\f\v", f_me->token[*j - k]);
	}
	return (0);
}

static char	literal_filler(int in_q, char c, t_token *f_me, int j)
{
	if ((in_q == 1 && c == '\'') || (in_q == 2 && c == '"')
		|| (!in_q && ft_strchr(" \t\f\v'\"", c)))
		f_me->literal[j] = 0;
	else if (c)
		f_me->literal[j] = 1;
	return (c);
}

/*
 * the amb redir return code of dollar expander is returned
 * to dollar exp helper
 */
int	dollar_expander(t_token *f_me, t_data *data, char *t, t_tok_s prev)
{
	int		i;
	int		j;
	int		in_q;

	i = -1;
	j = 0;
	in_q = 0;
	f_me->type = determine_type(t);
	while (t[++i])
	{
		determine_q(&in_q, t[i]);
		if (((in_q != 1 && t[i] == '$' && (t[i + 1] == '_' || t[i + 1] == '?'
						|| ft_isalpha(t[i + 1]))) || (t[i] == '~' && !i
					&& ft_strchr(" \t\f\v/", t[1]))) && prev != HDOC)
		{
			if (f_l_exp(fill_token(f_me, &t[i + 1], data, &j), f_me, in_q, &j))
				return (1);
			i += var_end(&t[i + 1]) - &t[i + 1];
		}
		else
			f_me->token[j] = literal_filler(in_q, t[i], f_me, j);
		j++;
	}
	f_me->token[j] = 0;
	return ((prev == REDIR) * unlit_spaces_probe(f_me));
}
