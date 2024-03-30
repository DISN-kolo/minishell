/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:01:48 by akozin            #+#    #+#             */
/*   Updated: 2024/03/30 13:26:16 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_token	*tokens_join(t_token *t1, t_token *t2) // TODO literal int array copy?
{
	t_token	*ret;
	int		i;
	int		j;

	ret = malloc(tokenslen(t1) + tokenslen(s2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (t1[j].token)
	{
		ret[i].token = ft_substr(t1[j].token, 0, ft_strlen(t1[j].token));
		i++;
		j++;
	}
	j = 0;
	while (t2[j].token)
	{
		ret[i].token = ft_substr(t2[j].token, 0, ft_strlen(t2[j].token));
		i++;
		j++;
	}
	ret[i].token = 0;
	return (ret);
}

t_token	*tokens_join_free(t_token *t1, t_token *t2)
{
	t_token	*ret;

	ret = tokens_join(t1, t2);
	if (t1)
		free_ret(&t1);
	return (ret);
}

/*
 * basically, an ft_split with "" in mind
 * like we have in tokenize, but isn't bothered by |<>& at all
 */
