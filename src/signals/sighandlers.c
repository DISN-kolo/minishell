/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:42:07 by akozin            #+#    #+#             */
/*   Updated: 2024/05/02 16:11:08 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libs/readline/readline.h"
#include "../../libs/readline/history.h"

void	handle_s_normal(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_err = 1;// TODO global error status here
	}
}

void	handle_s_hered(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "^C\n", 3);
		g_err = 1;// TODO global error status here
		// what do we do with it tho lol
		// like the normal data.errored? data.status_code?
	}
}
