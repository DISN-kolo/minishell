/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
/*   Updated: 2024/03/19 16:51:04 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline/readline.h"
#include "../readline/history.h"
#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	double_array_free(char ***a)
{
	int	i;

	i = 0;
	while (*a[i])
		free(*a[i++]);
	free(*a);
}

static void	exit_handler(t_data *data)
{
	int	i;

	double_array_free(&data->tokens);
	i = 0;
	while (data->coms[i].type != END)
	{
		dobule_array_free(&(data->coms[i].com));
		i++;
	}
	free(data->coms);
	printf("exit\n");
}

void	shell_loop(t_data *data)
{
	char	*s;

	s = readline("totally-not-bash $ ");
	while (s != 0)
	{
		add_history(s);
		tokenize_line(s, data);
		free(s);
		parse_line(data);
		expand_etc(data);
		redir_exec(data);
		s = readline("totally-not-bash $ ");
	}
	if (s == 0)
		exit_handler(data);
}
