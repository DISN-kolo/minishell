/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_rl_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:10:18 by akozin            #+#    #+#             */
/*   Updated: 2024/05/21 13:57:01 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libs/readline/readline.h"
#include "../../libs/readline/history.h"

int	fake_heredoc(char *eof)
{
	int		eoflen;
	char	*hline;

	eoflen = ft_strlen(eof);
	hline = NULL;
	while (1)
	{
		if (hline && !ft_strncmp(hline, eof, eoflen + 1))
			break ;
		if (hline)
			free(hline);
		hline = readline("> ");
		if (!hline)
			break ;
	}
	if (hline)
		free(hline);
	return (0);
}
