/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
/*   Updated: 2024/05/07 12:26:53 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libs/readline/readline.h"
#include "../libs/readline/history.h"

/*
 * ctrl-c = sigint
 * ctrl-\ = sigquit
 */
void	shell_loop(t_data *data)
{
	char	*s;

	while (1)
	{
		signal(SIGINT, handle_s_normal);
		signal(SIGQUIT, SIG_IGN);
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
		data->hd_counter = 0;
		free(s);
		get_heredocs(data);
		process_heredocs(data); // TODO
		if (token_loop(data))
			write(2, "run error\n", 10); //TODO err handeling
		data_cleaner(data);
	}
	bexit(data, NULL);
}
