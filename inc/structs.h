#ifndef STRUCTS_H
# define STRUCTS_H

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
} t_inout;

typedef struct s_com
{
	char		**com;
	t_inout		*ios;
	t_operator	oper;
	int			status;
	int			infd;
	int			outfd;
	int			amb_redir_ind;
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
	int		amb_tok_ind;
	int		amb_com_ind;
	char	*amb_tok_name;
	t_env	*env;
} t_data;

#endif
