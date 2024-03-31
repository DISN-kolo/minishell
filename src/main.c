/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:06:29 by akozin            #+#    #+#             */
/*   Updated: 2024/03/31 15:02:09 by molasz-a         ###   ########.fr       */
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
	data.env = create_env(envp);
	if (!data.env)
		return (1);
	shell_loop(&data);
	return (0);
}
