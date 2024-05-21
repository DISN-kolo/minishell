/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:37:44 by molasz-a          #+#    #+#             */
/*   Updated: 2024/05/21 15:22:28 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./errors.h"

/*
 * operators are &&, ||, |
 * redirs are >, <, >>, <<
 */

typedef enum e_tok_s
{
	TOKEN,
	HDOC,
	REDIR,
	REDIR_AMB,
	PIPE,
	AND,
	OR,
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
}	t_inout;

typedef struct s_com
{
	char		**com;
	t_inout		*ios;
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

typedef struct s_data
{
	t_token		*tokens;
	t_token		**tokens_list;
	t_com		*coms;
	t_hdoc		**hds;
	t_error		aux_error;
	int			local_status;
	int			coms_ind;
	int			hd_counter;
	int			hds_total_n;
	int			sp_hdoc;
	int			std_in;
	int			std_out;
	int			amb_tok_ind;
	char		*amb_tok_name;
	t_env		*env;
}	t_data;

#endif
