/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:20:41 by akozin            #+#    #+#             */
/*   Updated: 2024/03/30 13:47:39 by molasz-a         ###   ########.fr       */
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

// TOKENIZE
void	tokenize_line(char *s, t_data *data);
t_token	*tokenize_split(char *s);
int		tokenize_count(char *s, char *sep);
int		tokenize_err_probe(t_token *tokens);

// EXPAND & PARSE
void	parse_exec(t_data *data);
void	expand_vars(char *s, t_data *data);

// EXECUTION
void	redir_exec(t_data *data);

// ENVIROMENT
t_env	**create_env(char **envp);
char	**format_env(t_env *env);
char	*read_env(t_data *data, char *prop, int envi);
int		dup_env(t_data *data);

// BUILDINS
int		bexport(t_data *data, char **exports);
int		bunset(t_data *data, char **keys);
void	benv(t_data *data, int envi);

// FREE UTILS
void	free_double(char **p);
void	free_env(t_env *env);
int		free_ret(t_token **ret);
void	data_cleaner(t_data *data);

#endif
