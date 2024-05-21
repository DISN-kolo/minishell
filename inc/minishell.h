/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:20:41 by akozin            #+#    #+#             */
/*   Updated: 2024/05/21 13:34:43 by akozin           ###   ########.fr       */
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
# include <signal.h>

# include "../libs/libft/libft.h"
# include "./structs.h"

extern int	g_err;

// GENERAL
void		shell_loop(t_data *data);

// SIGNALS
void		handle_s_normal(int sig);
void		handle_s_hered(int sig);
void		default_sigs(void);

// TOKENIZE
t_error		tokenize(char *s, t_data *data);
int			tokenize_count(char *s, char *sep);
int			tokenize_err_probe(t_data *data, t_token *tokens);

// TOKEN UTILS
t_tok_s		determine_type(char *t);
char		*strchars(char *s, char *sep);

// GET HEREDOC
t_error		get_heredocs(t_data *data);
int			is_latest_hd(t_token *ts);

// TOKEN LOOP
t_error		token_loop(t_data *data);
t_token		**create_tokens_list(t_token *tokens);

// TOKEN LOOP UTILS
int			io_coms_alloc(t_com *coms, t_token *tokens, int u);
int			open_everything(t_data *data);
void		set_or_close_fds(t_data *data, int *i, int *fio);

// CMD LOOP
int			cmd_loop(t_data *data, t_token *tokens);
//+CMD FILLER
int			cmd_filler(t_data *data, int *i, t_token *ts);
int			cmd_filler_internal(t_data *data, int *i, t_token *ts, int *k);

// TOKEN EXPANSION
t_token		*token_expander(t_data *data, t_token *current_tokens);
int			init_te_data_linesave(int *i, t_token **new_tokens, t_data *data,
				t_token *exp_t);
int			dollar_exp_helper(t_token *exp_t, t_data *data,
				t_token *c_toks, int i);
int			dollar_expander(t_token *f_me, t_data *data, char *t, t_tok_s prev);
void		determine_q(int *in_q, char c);
t_tok_s		nt_prev(t_token *new_tokens);
int			unlit_spaces_probe(t_token *f_me);
char		*var_end(char *s);
t_token		*new_t_split(t_token *t);
t_token		*tokens_join_free(t_token *t1, t_token *t2);
int			tokenslen(t_token *t);
char		*strchars_lit(t_token *t, int k, char *sep);

// HEREDOC PROCESSIN'
t_error		process_heredocs(t_data *data);
char		*gen_h_fname(int *i);
int			heredoc_read_expand(t_data *data);
int			fake_heredoc(char *eof);
char		*hd_dollar_expander(char *l, t_data *data);

// EXPAND & PARSE
void		parse_exec(t_data *data);
int			io_coms_alloc(t_com *coms, t_token *tokens, int u);
void		expand_vars(char *s, t_data *data);

// RUNNER
int			run_cmds(t_data *data);
pid_t		run_cmd_multiple(t_data *data, int *end);
void		find_cmd(t_data *data, int i);
int			is_path(char *str);
int			run_builtin(t_data *data, int i, int ex);

// ENVIROMENT
t_env		*alloc_env(char **envp);
char		**format_env(t_data *data);
char		*read_env(t_data *data, char *prop);
int			dup_env(t_data *data);
int			find_equal(char *s);

// BUILTINS
int			becho(char **args);
int			bcd(t_data *data, char **args);
int			bpwd(t_data *data);
int			bexport(t_data *data, char **exports);
int			export_env(t_data *data, char *exp);
int			bunset(t_data *data, char **keys);
int			benv(t_data *data);
int			bexit(t_data *data, char **args);

// FREE UTILS
void		free_double(char **p);
void		free_tokens(t_token *tokens);
void		free_token_list(t_token **token_list);
void		free_coms(t_com *coms);
void		free_heredocs(t_hdoc **heredocs);
void		data_cleaner(t_data *data);
void		free_env(t_env *env);

// ERROR UTILS
void		print_error(char *cmd, char *var, char *error);
void		print_perror(char *msg, int error);
void		tokenize_error(char *token);

// MISC
char		*ft_strjoin_free(char *s1, char *s2);
void		exit_handler(t_data *data, int exit_code);

#endif
