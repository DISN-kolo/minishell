/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:15:48 by akozin            #+#    #+#             */
/*   Updated: 2024/03/31 14:57:12 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../readline/readline.h"
#include "../readline/history.h"

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
	bexit(data, NULL);
}
