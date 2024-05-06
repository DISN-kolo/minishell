/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:06:29 by akozin            #+#    #+#             */
/*   Updated: 2024/05/06 13:30:46 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	data.tokens = 0;
	data.coms = 0;
	data.errored = 0;
	data.status_code = 0;
	data.std_in = dup(0);
	data.std_out = dup(1);
	if (data.std_in < 0 || data.std_out < 0)
		return (1);
	data.env = alloc_env(envp);
	if (!data.env)
		return (1);
	shell_loop(&data);
	return (0);
}
