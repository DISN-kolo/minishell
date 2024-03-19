/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
/*   Updated: 2024/03/19 16:31:03 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline/readline.h"
#include "../readline/history.h"
#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	shell_loop(t_data *data)
{
	char	*s;

	s = readline("totally-not-bash $ ");
	while (s != 0)
	{
		add_history(s);
		tokenize_line(s, data);
		parse_line(data);
		free(s);
		s = readline("totally-not-bash $ ");
	}
	if (s == 0)
		printf("exit\n");
}
