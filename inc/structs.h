/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:37:44 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/08 11:39:46 by molasz-a         ###   ########.fr       */
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
	OR,
	O_BRACKET,
	C_BRACKET
}	t_tok_s;

/*
 * expand -- for hdoc only!
 */
typedef struct s_inout
{
	int		in;
	int		dub;
	char	*fname;
	int		expand;
	int		amb;
}	t_inout;

typedef struct s_com
{
	char		**com;
	t_inout		*ios;
	int			status;
	int			infd;
	int			outfd;
	int			amb_redir_ind;
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
	int		latest;
	int		expand;
}	t_hdoc;

typedef struct s_cmdtree
{
	struct s_cmdtree	*left;
	struct s_cmdtree	*right;
	t_token				*tokens;
	int					brackets;
}	t_cmdtree;

typedef struct s_data
{
	t_token		*tokens;
	t_cmdtree	*cmdtree;
	t_com		*coms;
	t_hdoc		**hds;
	int			hd_counter;
	int			std_in;
	int			std_out;
	int			status_code;
	int			skip_cmd;
	int			skip_brackets;
	int			amb_tok_ind;
	char		*amb_tok_name;
	t_env		*env;
}	t_data;

#endif
