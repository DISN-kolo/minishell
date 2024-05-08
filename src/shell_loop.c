/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
/*   Updated: 2024/05/08 16:22:17 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libs/readline/readline.h"
#include "../libs/readline/history.h"

static int	loop_calls(t_data *data, char *s)
{
	add_history(s);
	if (tokenize(s, data))
		return (1);
	if (get_heredocs(data))
		return (1);
	if (process_heredocs(data))
		return (1);
	if (operators_tree(data))
		return (1);
	if (token_loop(data))
		return (1);
	return (0);
}

// ctrl-c = sigint
// ctrl-\ = sigquit
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
		if (loop_calls(data, s))
			ft_putendl_fd("Run error", 2);
		free(s);
		data_cleaner(data);
	}
	bexit(data, NULL);
}
