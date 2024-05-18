/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
/*   Updated: 2024/05/18 13:13:12 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libs/readline/readline.h"
#include "../libs/readline/history.h"

static void	handle_errors(t_data *data, t_error error)
{
	if (error == SYNTAX_ERR)
		tokenize_error(data->tokens[data->sp_hdoc].token);
	else if (data->aux_error == LEFT_Q_ERR)
		write(2, "minishell: un-closed quotations left\n", 37);
	else if (error == HDOC_LIMIT_ERR)
	{
		write(2, "minishell: maximum here-document count exceeded\n", 48);
		exit_handler(data, 2);
	}
	else if (data->aux_error == MALLOC_ERR || error == MALLOC_ERR)
		print_perror("MALLOC error", -1);
	else if (error == FORK_ERR)
		print_perror("FORK error", -1);
}

static void	small_lcs_init(t_data *data, char *s)
{
	data->aux_error = NULL_ERR;
	if (s && s[0])
		add_history(s);
}

static int	loop_calls(t_data *data, char *s)
{
	t_error	error;

	error = tokenize(s, data);
	small_lcs_init(data, s);
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
	if (data->sp_hdoc > 0)
		return (SYNTAX_ERR);
	if (data->local_status)
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
		handle_errors(data, error);
		free(s);
		data_cleaner(data);
	}
	bexit(data, NULL);
}
