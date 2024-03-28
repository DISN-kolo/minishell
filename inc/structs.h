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
	int status;
} t_com;

typedef struct s_token
{
	char *token;
	int *literal;
} t_token;

typedef struct s_data
{
	t_token *tokens;
	t_com *coms;
	int errored;
	char ***env;
} t_data;

#endif
