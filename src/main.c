/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:06:29 by akozin            #+#    #+#             */
/*   Updated: 2024/03/27 14:04:01 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_list	*env_alloc(char **envp)
{
	t_list	*env_list;
	t_list	*lst_env;
	t_list	*lst_new;
	char	*tmp;
	int		i;

	i = -1;
	lst_env = NULL;
	while (envp[++i])
	{
		tmp = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		if (!tmp)
			return (ft_lstclear(&lst_env, free), NULL);
		lst_new = ft_lstnew(tmp);
		if (!lst_new)
		{
			free(tmp);
			return (ft_lstclear(&lst_env, free), NULL);
		}
		ft_lstadd_back(&lst_env, lst_new);
	}
	env_list = ft_lstnew(lst_env);
	if (!env_list)
		return (ft_lstclear(&lst_env, free), NULL);
	return (env_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	data.tokens = 0;
	data.coms = 0;
	data.errored = 0;
	data.env = env_alloc(envp);
	if (!data.env)
		return (1);
	shell_loop(&data);
	return (0);
}
