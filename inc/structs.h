/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:37:44 by molasz-a          #+#    #+#             */
/*   Updated: 2024/04/24 19:38:50 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
 * operators are &&, ||, |
 * redirs are >, <, >>, <<
 */

typedef enum e_tok_s
{
	TOKEN,
	HDOC,
	REDIR,
	PIPE,
	AND,
	OR
}	t_tok_s;

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
	int			status;
}	t_com;

typedef struct s_token
{
	char	*token;
	int		*literal;
	t_tok_s	type;
}	t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		exp;
}	t_env;

/*
 * expand? yeah -> we expand $ inside
 * nah -> we don't
 * determined by whether the hdoc str is in quotations or no (wow)
 */
typedef struct s_hdoc
{
	char	*str;
	int		expand;
}	t_hdoc;

typedef struct s_data
{
	t_token	*tokens;
	t_com	*coms;
	t_hdoc	**hds;
	int		std_in;
	int		status_code;
	int		errored;
	t_env	*env;
}	t_data;

#endif
