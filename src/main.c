/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:06:29 by akozin            #+#    #+#             */
/*   Updated: 2024/03/28 12:56:42 by molasz-a         ###   ########.fr       */
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
	printf("ENV 0\n");
	print_env(&data, 0);
	bexport(&data, ft_split("marti=hola artem=heheh =hola a=A", ' '));
	printf("\nENV 1\n");
	print_env(&data, 1);
	bunset(&data, ft_split("marti artem a hola", ' '));
	printf("\nENV 2\n");
	print_env(&data, 2);
	shell_loop(&data);
	return (0);
}
