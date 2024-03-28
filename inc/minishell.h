/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:20:41 by akozin            #+#    #+#             */
/*   Updated: 2024/03/28 15:44:24 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

# include "../libft/libft.h"

/*
 * operators are &&, ||, |
 * redirs are >, <, >>, <<
 */

typedef enum e_operator
{
	AND,
	OR,
	PIPE
}	t_operator;

typedef struct s_inout
{
	int		dub;
	char	*fname;
}	t_inout;

typedef struct s_com
{
	char		**com;
	t_inout		*ins;
	t_inout		*outs;
	int			envi;
	t_operator	oper;
	int			status;
}	t_com;

typedef struct s_token
{
	char	*token;
	int		*literal;
}	t_token;

typedef struct s_data
{
	t_token	*tokens;
	t_com	*coms;
	int		errored;
	char	***env;
}	t_data;

void	shell_loop(t_data *data);

void	tokenize_line(char *s, t_data *data);
char	*strchars(char *s, char *sep);
int		valid_operator(char *s, int *i);
int		t_split_internal(char **str, t_token **ret, int *i);
int		t_c_internal_else(char *s, char *sep, int *in_q, int i);
int		t_err_probe(t_token *tokens);
int		tokenize_error(t_token token, int i);


void	parse_exec(t_data *data);
void	expand_vars(char *s, t_data *data);

void	redir_exec(t_data *data);

// ENVIROMENT
char	***create_env(char **envp);
int		dup_env(t_data *data);
char	*read_env(t_data *data, char *prop, int envi);
void	print_env(t_data *data, int envi);
int		bexport(t_data *data, char **exports);
int		bunset(t_data *data, char **keys);

// FREE UTILS
void	free_double(char **p);
int		free_ret(t_token **ret);
void	data_cleaner(t_data *data);

#endif
