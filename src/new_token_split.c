/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:07:37 by akozin            #+#    #+#             */
/*   Updated: 2024/03/30 17:13:45 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../inc/minishell.h>

t_token	*new_t_split(t_token t)
{
	t_token	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof (t_token) * (new_token_c(t, " \t\f\v") + 1));
	if (!ret)
		return (NULL);
	while (*str)
	{
		while (ft_strchr(" \t\f\v", *t.token) && *t.token)
			t.token++;
		if (*t.token)
		{
			if (new_t_split_internal(&t, &ret, &i))
				return (NULL);
		}
	}
	ret[i].token = NULL;
	return (ret);
}
