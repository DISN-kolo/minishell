/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:01:48 by akozin            #+#    #+#             */
/*   Updated: 2024/04/05 13:45:02 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*var_end(char *s)
{
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

	ret = 0;
	if (!t)
		return (-200);
	while (t[ret].token)
		ret++;
	return (ret);
}

t_token	*tokens_join(t_token *t1, t_token *t2) // TODO literal int array copy?
{
	t_token	*ret;
	int		i;
	int		j;

	if (!t1)
		return (t2);
	if (!t2)
		return (printf("somehow t2 is null!\n"), NULL);
	ret = malloc(sizeof (t_token) * (tokenslen(t1) + tokenslen(t2) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (t1[j].token)
	{
		ret[i++].token = ft_substr(t1[j].token, 0, ft_strlen(t1[j].token));
		j++;
	}
	j = 0;
	while (t2[j].token)
	{
		ret[i++].token = ft_substr(t2[j].token, 0, ft_strlen(t2[j].token));
		j++;
	}
	ret[i].token = 0;
	return (ret);
}

t_token	*tokens_join_free(t_token *t1, t_token *t2)
{
	t_token	*ret;

	ret = tokens_join(t1, t2);
//	if (t1) // TODO
//		free_ret(&t1);
	t1 = NULL;
	return (ret);
}
