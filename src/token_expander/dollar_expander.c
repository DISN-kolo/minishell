/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:26:06 by akozin            #+#    #+#             */
/*   Updated: 2024/04/03 16:56:39 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int fill_token(t_token *f_me, char *t, t_data *data, int *j)
{
	char	*env_v_name;
	char	*env_v_val;
	int		k;

	k = 0;
	printf("\t\tentered fill token\n");
	env_v_name = ft_substr(t, 0, var_end(t) - t);
	printf("\t\t\tsubstr success:\n"
			"\t\t\tenv_v_name = %s\n", env_v_name);
	env_v_val = read_env(data, env_v_name, 0); // TODO envi removal
	printf("\t\t\tread_env success:\n"
			"\t\t\tenv_v_val  = %s\n", env_v_val);
	if (!env_v_val)
		return (-1);
	while (env_v_val[k])
	{
		printf("k: %2d char: %c\n", k, env_v_val[k]);
		f_me->token[*j] = env_v_val[k];
		printf("j: %2d eq OK\n", *j);
		k++;
		(*j)++;
	}
	f_me->token[*j] = 0; // TODO check if it screws us up. should fix the ft_strchr in the fill_lit_expanded tho
	(*j)--;
//	free(env_v_name);
	return (k);
}
/* ^ use k to know how many ints to fill in the literals arr
 */

static void	determine_q(int *in_q, char c)
{
	if ((*in_q == 1 && c == '\'') || (*in_q == 2 && c == '"'))
		*in_q = 0;
	else if (!*in_q && (c == '\'' || c == '"'))
		*in_q = (c == '"') + 1;
}

static void	fill_lit_expanded(int k, t_token *f_me, int in_q, int j)
{
	printf("\t\tentered fill lit expanded\n");
	while (k-- > 0)
	{
		f_me->literal[j - k] = in_q
			|| !ft_strchr(" \t\f\v", f_me->token[j - k]);
	}
}

static void	literal_filler(int in_q, char c, t_token *f_me, int j)
{
	printf("\t\tentered literal filler token\n");
	if ((in_q == 1 && c == '\'') || (in_q == 2 && c == '"')
			|| (!in_q && ft_strchr(" \t\f\v'\"", c)))
		f_me->literal[j] = 0;
	else
		f_me->literal[j] = 1;
}

/*
 * envi here, to later send it to other funcs who need it or smthn
 * MUST ADD, TODO
 */
void	dollar_expander(t_token *f_me, t_data *data, char *t)
{
	int		i;
	int		j;
	int		in_q;

	i = 0;
	j = 0;
	in_q = 0;
	printf("\tentered dollar expander\n");
	while (t[i])
	{
		determine_q(&in_q, t[i]);
		if (in_q != 1 && t[i] == '$'
				&& (t[i + 1] == '_' || ft_isalpha(t[i + 1])))
		{
			fill_lit_expanded(fill_token(f_me, &t[i + 1], data, &j),
					f_me, in_q, j);
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
