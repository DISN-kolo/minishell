/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:20:41 by akozin            #+#    #+#             */
/*   Updated: 2024/03/25 13:02:22 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include "../libft/libft.h"

/*
 * operators are &&, ||, |
 * redirs are >, <, >>, <<
 */
typedef enum e_wtype
{
	COMMAND,
	OPERATOR,
	REDIR,
	END
}	t_wtype;

typedef struct s_com
{
	t_wtype	type;
	char	**com;
}	t_com;

typedef struct s_data
{
	char	**tokens;
	t_com	*coms;
	int		errored;
	t_list	*env;
}	t_data;

void	shell_loop(t_data *data);

void	tokenize_line(char *s, t_data *data);
int		valid_operator(char *s, int *i);

void	parse_line(t_data *data);

void	expand_etc(t_data *data);

void	redir_exec(t_data *data);

#endif
