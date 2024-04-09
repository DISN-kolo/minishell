/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:20:41 by akozin            #+#    #+#             */
/*   Updated: 2024/04/09 16:11:43 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

# include "../libft/libft.h"
# include "./structs.h"

// GENERAL
void	shell_loop(t_data *data);
int		token_loop(t_data *data);

// TOKENIZE
void	tokenize_line(char *s, t_data *data);
t_token	*tokenize_split(char *s);
int		tokenize_count(char *s, char *sep);
int		tokenize_err_probe(t_token *tokens);

// TOKEN EXPANSION
void	token_expander(t_data *data, t_token **current_tokens);
void	dollar_expander(t_token *f_me, t_data *data, char *t);
char	*var_end(char *s);
t_token	*new_t_split(t_token t);
t_token	*tokens_join_free(t_token *t1, t_token *t2);
int		tokenslen(t_token *t);
char	*strchars_lit(t_token *t, int k, char *sep);

// EXPAND & PARSE
void	parse_exec(t_data *data);
void	expand_vars(char *s, t_data *data);

// EXECUTION
int		run_cmds(t_data *data);

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

#endif
