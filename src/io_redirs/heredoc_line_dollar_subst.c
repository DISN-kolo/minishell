/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_line_dollar_subst.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:49:51 by akozin            #+#    #+#             */
/*   Updated: 2024/05/21 14:24:38 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	fill_hd_l(char *nl, char *l, t_data *data, int *j)
{
	char	*env_v_name;
	char	*env_v_val;
	int		k;

	k = 0;
	env_v_name = ft_substr(l, 0, var_end(l) - l);
	env_v_val = read_env(data, env_v_name);
	if (!env_v_val)
		return (free(env_v_name), (*j)--, (void)0);
	while (env_v_val[k])
	{
		nl[*j] = env_v_val[k];
		k++;
		(*j)++;
	}
	(*j)--;
	free(env_v_name);
	free(env_v_val);
}

static int	hd_inside_dollar_counter(t_data *data, char *t, int i)
{
	int		ret;
	char	*env_v_name;
	char	*env_v_val;

	if (t[i + 1] != '_' && !ft_isalpha(t[i + 1]) && t[i + 1] != '?')
		return (0);
	env_v_name = ft_substr(&t[i + 1], 0, var_end(&t[i + 1]) - &t[i + 1]);
	env_v_val = read_env(data, env_v_name);
	if (!env_v_val)
	{
		ret = ft_strlen(env_v_name);
		return (free(env_v_name), -ret);
	}
	ret = ft_strlen(env_v_val) - ft_strlen(env_v_name);
	free(env_v_val);
	free(env_v_name);
	return (ret);
}

static int	hd_expansion_counter(t_data *data, char *t)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (t[i])
	{
		if (t[i] == '$' && (t[i + 1] == '_' || t[i + 1] == '?'
				|| ft_isalpha(t[i + 1])))
			ret += hd_inside_dollar_counter(data, t, i) - 1;
		i++;
	}
	return (i + ret);
}

/*
 * this differs from dollar expander.
 * 1. we have no '" intergation (=> no literal. all is literal!)
 * 2. we have no token types (no tokens at all lol)
 * 3. we have no ~ expansion
 *
 * since it's gnl, we'll have a \n as a pre-terminator. it shoudln't affect us
 * BUT if it does... well, we know where to look :)
 */
char	*hd_dollar_expander(char *l, t_data *data)
{
	int		i;
	int		j;
	char	*nl;

	i = 0;
	j = 0;
	nl = malloc(hd_expansion_counter(data, l) + 1);
	if (!nl)
		return (NULL);
	while (l[i])
	{
		if (l[i] == '$' && (l[i + 1] == '_' || l[i + 1] == '?'
				|| ft_isalpha(l[i + 1])))
		{
			fill_hd_l(nl, &l[i + 1], data, &j);
			i += var_end(&l[i + 1]) - &l[i + 1];
		}
		else
			nl[j] = l[i];
		j++;
		i++;
	}
	nl[j] = 0;
	free(l);
	return (nl);
}
