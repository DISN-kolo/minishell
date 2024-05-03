/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:20:41 by akozin            #+#    #+#             */
/*   Updated: 2024/05/02 22:00:33 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "../libs/libft/libft.h"
# include "./structs.h"

// GENERAL
void	shell_loop(t_data *data);
int		token_loop(t_data *data);

// TOKENIZE
void	tokenize_line(char *s, t_data *data);
t_token	*tokenize_split(char *s);
char	*strchars(char *s, char *sep);
int		tokenize_count(char *s, char *sep);
int		tokenize_err_probe(t_token *tokens);

// HEREDOC GRABBIN'
void	get_heredocs(t_data *data);
int		is_latest_hd(t_token *ts);

// OPERATORS
t_cmdtree	*cmdtree_create(t_token *tokens);

// TOKEN LOOP UTILS
int		io_coms_alloc(t_com *coms, t_token *tokens, int u);
int		open_everything(t_data *data);
//+CMD LOOP
int		cmd_loop(t_data *data, t_token *tokens);
//+CMD FILLER
int		cmd_filler(t_data *data, int *i, t_token *ts);
int		cmd_filler_internal(t_data *data, int *i, t_token *ts, int *k);

// TOKEN EXPANSION
t_token	*token_expander(t_data *data, t_token *current_tokens, int *count);
int		init_te_data_linesave(int *i, t_token **new_tokens, t_data *data);
int		dollar_exp_helper(t_token *exp_t, t_data *data, t_token *c_toks, int i);
int		dollar_expander(t_token *f_me, t_data *data, char *t, t_tok_s prev);
void	determine_q(int *in_q, char c);
t_tok_s	determine_type(char *t);
t_tok_s	nt_prev(t_token *new_tokens);
int		unlit_spaces_probe(t_token *f_me);
char	*var_end(char *s);
t_token	*new_t_split(t_token t);
t_token	*tokens_join_free(t_token *t1, t_token *t2);
int		tokenslen(t_token *t);
char	*strchars_lit(t_token *t, int k, char *sep);

// HEREDOC PROCESSIN'
int		process_heredocs(t_data *data);
char	*gen_h_fname(int *i);
char	*ft_strjoin_free(char *b1, char *b2);
int		heredoc_read_expand(t_data *data);
void	hd_coords(int *hdi, int n, t_data *data);
char	*hd_dollar_expander(char *l, t_data *data);

// EXPAND & PARSE
void	parse_exec(t_data *data);
int		io_coms_alloc(t_com *coms, t_token *tokens, int u);
void	expand_vars(char *s, t_data *data);

// EXECUTION
int		run_cmds(t_data *data);
void	find_cmd(t_data *data, int i);
int		is_path(char *str);

// ENVIROMENT
t_env	*alloc_env(char **envp);
char	**format_env(t_data *data);
char	*read_env(t_data *data, char *prop);
int		dup_env(t_data *data);
int		find_equal(char *s);

// BUILTINS
void	becho(char **args);
void	bcd(t_data *data, char **args);
void	bpwd(t_data *data, char **args);
int		bexport(t_data *data, char **exports);
int		export_env(t_data *data, char *exp);
int		bunset(t_data *data, char **keys);
void	benv(t_data *data);
void	bexit(t_data *data, char **args);

// FREE UTILS
void	free_double(char **p);
void	free_env(t_env *env);
int		free_ret(t_token **ret);
void	data_cleaner(t_data *data);
void	free_coms(t_data *data);

// ERROR UTILS
void	print_error(char *cmd, char *var, char *error);
void	print_perror(char *msg, int error);

#endif
