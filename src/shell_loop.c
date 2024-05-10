/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
/*   Updated: 2024/05/10 12:12:24 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libs/readline/readline.h"
#include "../libs/readline/history.h"

static void	handle_errors(t_error error)
{
	if (error == MALLOC_ERR)
		print_perror("MALLOC error", -1);
	else if (error == FORK_ERR)
		print_perror("FORK error", -1);
}

static t_error	loop_calls(t_data *data, char *s)
{
	t_error	error;

	data->stop_hdoc = -1;
	add_history(s);
	error = tokenize(s, data);
	if (error >= MALLOC_ERR)
		return (error);
	if (!data->tokens[0].token)
		return (NULL_ERR);
	error = get_heredocs(data);
	if (error >= MALLOC_ERR)
		return (error);
	error = process_heredocs(data);
	if (error >= MALLOC_ERR)
		return (error);
	if (data->stop_hdoc != -1)
		return (NULL_ERR);
	error = token_loop(data);
	if (error >= MALLOC_ERR)
		return (error);
	return (0);
}

// ctrl-c = sigint
// ctrl-\ = sigquit
void	shell_loop(t_data *data)
{
	t_error	error;
	char	*s;

	while (1)
	{
		signal(SIGINT, handle_s_normal);
		signal(SIGQUIT, SIG_IGN);
		s = readline("totally-not-bash $ ");
		if (!s)
			break ;
		error = loop_calls(data, s);
		handle_errors(error);
		free(s);
		data_cleaner(data);
	}
	bexit(data, NULL);
}
