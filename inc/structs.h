#ifndef STRUCTS_H
#define STRUCTS_H

/*
 * operators are &&, ||, |
 * redirs are >, <, >>, <<
 */

typedef enum e_operator
{
	NONE,
	AND,
	OR
}	t_operator;

typedef enum e_tok_s
{
	TOKEN,
	HDOC,
	REDIR,
	PIPE
}	t_tok_s;

typedef struct s_inout
{
	int		dub;
	char	*fname;
} t_inout;

typedef struct s_com
{
	char		**com;
	t_inout		*ins;
	t_inout		*outs;
	t_operator	oper;
	int			status;
} t_com;

typedef struct s_token
{
	char	*token;
	int		*literal;
	t_tok_s	type;
} t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		exp;
} t_env;

/*
 * expand? yeah -> we expand $ inside
 * nah -> we don't
 * determined by whether the hdoc str is in quotations or no (wow)
 */
typedef struct	s_hdoc
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
} t_data;

#endif
