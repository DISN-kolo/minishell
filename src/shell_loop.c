/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
/*   Updated: 2024/04/09 14:12:02 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../readline/readline.h"
#include "../readline/history.h"

static void	token_printer(t_token *t)
{
	int	i;

	i = 0;
	while (t[i].token)
	{
		printf("'%s'\n", t[i].token);
		i++;
	}
}

void	shell_loop(t_data *data)
{
	char	*s;

	while (1)
	{
		s = readline("totally-not-bash $ ");
		if (!s)
			break ;
		if (!s[0])
		{
			free(s);
			continue ;
		}
		add_history(s);
		tokenize_line(s, data);
		free(s);
//		token_loop(data);
/*
 * this ^^^^^^^^^^^^^^^^ we must use
 * now THIS we don't use; i'm just doing it to debug token expansion
 *      vvv
 */
		token_expander(data, data->tokens);
		token_printer(data->tokens);
		data_cleaner(data);
	}
	bexit(data, NULL);
}
