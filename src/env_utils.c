/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:23:31 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/27 14:05:24 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*env_read(t_data *data, char *prop, int envi)
{
	t_list	*lst;
	char	*value;
	char	*key;

	key = ft_strjoin(prop, "=");
	if (!key)
		return (NULL);
	lst = data->env;
	while (lst)
	{
		if (!ft_strncmp(key, lst->content, ft_strlen(key)))
			break ;
		lst = lst->next;
	}
	if (lst)
		value = lst->content + ft_strlen(key);
	else
		value = "";
	return (value);
}

static int	env_add(t_data *data, char *export)
{
	t_list	*lst;
	char	*str;

	str = ft_substr(export, 0, ft_strlen(export));
	if (!str)
		return (1);
	lst = ft_lstnew(str);
	if (!lst)
		return (free(str), 1);
	return (ft_lstadd_back(&data->env, lst), 0);
}

int	env_export(t_data *data, char *export)
{
	int		i;
	t_list	*lst;

	i = 0;
	while (export[i] && export[i] != '=')
		i++;
	if (i == (int)ft_strlen(export))
		return (0);
	lst = data->env;
	while (lst)
	{
		if (!ft_strncmp(export, lst->content, i))
			break ;
		lst = lst->next;
	}
	if (lst)
	{
		free(lst->content);
		lst->content = ft_substr(export, 0, ft_strlen(export));
		if (!lst->content)
			return (1);
	}
	else if (env_add(data, export))
		return (1);
	return (0);
}

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
	lst = data->env;
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
