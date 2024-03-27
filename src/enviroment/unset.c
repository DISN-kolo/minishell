/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:13:41 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/27 14:55:26 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	env_remove(t_data *data, t_list *lst, int i)
{
	t_list	*tmp;

	tmp = lst->next;
	free(lst->content);
	free(lst);
	if (i)
	{
		lst = data->env;
		while (i-- > 1)
		{
			lst = lst->next;
		}
		lst->next = tmp;
	}
	else
		data->env = tmp;
}

int	env_unset(t_data *data, char *prop)
{
	t_list	*lst;
	char	*key;
	int		i;

	key = ft_strjoin(prop, "=");
	if (!key)
		return (1);
	i = 0;
	lst = update_env(data);
	while (lst)
	{
		if (!ft_strncmp(key, lst->content, ft_strlen(key)))
			break ;
		lst = lst->next;
		i++;
	}
	if (lst)
		env_remove(data, lst, i);
	return (0);
}
