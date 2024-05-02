/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:06:29 by akozin            #+#    #+#             */
/*   Updated: 2024/05/02 13:47:22 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libs/readline/readline.h"
#include "../libs/readline/history.h"
#include <signal.h>

void	handle(int sig)
{
	//write(2, "sig: ", 5);
	//write(2, sig == SIGINT ? "int " : sig == SIGQUIT ? "quit" : "tstp", 4);
	//write(2, "\n", 1);
	//printf("%d\n", sig);
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
 * ctrl-c = sigint
 * ctrl-\ = sigquit
 * ctrl-z = sigstop
 */
int	main(int argc, char **argv, char **envp)
{
	t_data				data;
	struct sigaction	s_sa;

	s_sa.sa_handler = &handle;
	s_sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_sa, NULL);
	sigaction(SIGTSTP, &s_sa, NULL);
	(void) argc;
	(void) argv;
	data.tokens = 0;
	data.coms = 0;
	data.errored = 0;
	data.status_code = 0;
	data.env = alloc_env(envp);
	if (!data.env)
		return (1);
	shell_loop(&data);
	return (0);
}
