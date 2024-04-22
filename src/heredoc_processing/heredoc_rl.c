/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_rl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:13:57 by akozin            #+#    #+#             */
/*   Updated: 2024/04/22 11:37:57 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../readline/readline.h"
#include "../../readline/history.h"

/*
 * i[0] goes thru the first array, which contains hds as arrays between operators,
 * i.e. &&s and ||s.
 * i[1] goes thru the second arrays, getting each heredoc.
 * j[0] goes thru the commands, j[1] goes thru their ins.
 * i don't think we need a total counter.
 */
int	process_heredocs(t_data *data)
{
	int	i[2];
//	int	j[2];

	i[0] = 0;
//	j[0] = 0;
//	j[1] = 0;
	while (data->hds[i[0]])
	{
		i[1] = 0;
		while (data->hds[i[0]][i[1]].str)
		{
			printf("data->hds[%2d][%2d].str = '%s', exp: %d\n", i[0], i[1], data->hds[i[0]][i[1]].str, data->hds[i[0]][i[1]].expand);
			/*
			if (!data->coms[j[0]].ins[j[1] + 1].fname)
			{
				j[0]++;
				j[1] = 0;
			}
			else
				j[1]++;
			*/
			i[1]++;
		}
		printf("==\n");
		i[0]++;
	}
//
//
//	int		i;
//	char	*hline;
//
//	 = 0;
//	hline = readline("> ");
//	while (hline && ft_strncmp(hline, "forcedoc", 8))
//	{
//		printf("last line was '%s'\n", hline);
//		hline = readline("> ");
//		if (!data->hds)
//			return (1);
//	}
	return (0);
}
