/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/28 15:35:29 by akozin           ###   ########.fr       */
=======
/*   Updated: 2024/03/28 13:37:57 by molasz-a         ###   ########.fr       */
>>>>>>> 1e21c537792d8d973cfa0e1d4a23fa3403ba9766
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../readline/readline.h"
#include "../readline/history.h"

static void	exit_handler(t_data *data)
{
	data_cleaner(data);
	printf("exit\n");
}

void	shell_loop(t_data *data)
{
	char	*s;

	while (1)
	{
		s = readline("totally-not-bash $ ");
		if (!s)
			break ;
		add_history(s);
		tokenize_line(s, data);
		free(s);
//		parse_exec(data);
		data_cleaner(data);
	}
	exit_handler(data);
}
