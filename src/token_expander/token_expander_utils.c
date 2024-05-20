/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:01:48 by akozin            #+#    #+#             */
/*   Updated: 2024/05/20 13:06:47 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*var_end(char *s)
{
	if (*s == '?')
		return (s + 1);
	if (*(s - 1) == '~')
		return (s);
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (s);
		s++;
	}
	return (s);
}

int	tokenslen(t_token *t)
{
	int	ret;

	if (!t)
		return (0);
	ret = 0;
	while (t[ret].token)
		ret++;
	return (ret);
}

t_token	*tokens_join(t_token *t1, t_token *t2)
{
	t_token	*ret;
	int		i[2];

	ret = malloc(sizeof (t_token) * (tokenslen(t1) + tokenslen(t2) + 1));
	if (!ret)
		return (NULL);
	i[0] = 0;
	i[1] = -1;
	while (t1 && t1[++i[1]].token)
	{
		ret[i[0]].type = t1[i[1]].type;
		ret[i[0]].literal = NULL;
		ret[i[0]++].token = ft_strdup(t1[i[1]].token);
	}
	i[1] = -1;
	while (t2 && t2[++i[1]].token)
	{
		ret[i[0]].type = t2[i[1]].type;
		ret[i[0]].literal = NULL;
		ret[i[0]++].token = ft_strdup(t2[i[1]].token);
	}
	ret[i[0]].token = NULL;
	return (ret);
}

t_token	*tokens_join_free(t_token *t1, t_token *t2)
{
	t_token	*ret;
	int		len1;
	int		len2;

	len1 = tokenslen(t1);
	len2 = tokenslen(t2);
	if (len1 + len2 < 0)
		return (NULL);
	ret = tokens_join(t1, t2);
	free_tokens(t1);
	free_tokens(t2);
	return (ret);
}
