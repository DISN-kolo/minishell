#ifndef STRUCTS_H
#define STRUCTS_H

/*
 * operators are &&, ||, |
 * redirs are >, <, >>, <<
 */

typedef enum e_operator
{
	AND,
	OR,
	PIPE
} t_operator;

typedef struct s_inout
{
	int dub;
	char *fname;
} t_inout;

typedef struct s_com
{
	char **com;
	t_inout *ins;
	t_inout *outs;
	int envi;
	t_operator oper;
} t_com;

typedef struct s_token
{
	char *token;
	int *literal;
} t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		exp;
} t_env;

typedef struct s_data
{
	t_token *tokens;
	t_com *coms;
	int status_code;
	int errored;
	t_env *env;
} t_data;

#endif
