# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 16:38:42 by akozin            #+#    #+#              #
#    Updated: 2024/05/21 16:17:00 by akozin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libs/libft/
LIBFT_A = $(addprefix $(LIBFT), libft.a)

GNL = libs/gnl/
GNL_A = $(addprefix $(GNL), libgnl.a)

RL = libs/readline/
RL_A = $(addprefix $(RL), libreadline.a)
RLHIST_A = $(addprefix $(RL), libhistory.a)
RL_URL = http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz
RL_FILE = readline-master.tar.gz

NAME = minishell

MAKE = make

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
DEFS = -DREADLINE_LIBRARY

SRCNAMES = main.c \
			shell_loop.c \
			signals/sighandlers.c \
			tokenize/tokenize.c \
			tokenize/tokenize_count.c \
			tokenize/tokenize_err_probe.c \
			get_heredocs/get_heredocs.c \
			get_heredocs/get_heredocs_utils.c \
			heredoc_processing/heredoc_rl.c \
			heredoc_processing/heredoc_rl_utils.c \
			heredoc_processing/heredoc_filename_creator.c \
			token_loop/token_loop.c \
			token_loop/token_loop_utils.c \
			token_loop/token_list.c \
			token_loop/cmd_loop.c \
			token_loop/cmd_filler.c \
			token_loop/cmd_filler_utils.c \
			token_expander/token_expander.c \
			token_expander/token_expander_utils.c \
			token_expander/token_expander_utils_2.c \
			token_expander/dollar_expander.c \
			token_expander/new_token_splitter.c \
			token_expander/new_token_splitter_utils.c \
			io_redirs/io_redirs_handler.c \
			io_redirs/io_redirs_handler_utils.c \
			io_redirs/heredoc_read_expand.c \
			io_redirs/heredoc_line_dollar_subst.c \
			runner/run_cmds.c \
			runner/find_cmd.c \
			runner/find_cmd_utils.c \
			builtins/echo.c \
			builtins/cd.c \
			builtins/pwd.c \
			builtins/export.c \
			builtins/export_utils.c \
			builtins/unset.c \
			builtins/env.c \
			builtins/exit.c \
			utils/free_utils.c \
			utils/clean_utils.c \
			utils/error_utils.c \
			utils/token_utils.c \
			enviroment.c \

SRCS = $(SRCNAMES)
OBJS = $(addprefix obj/, $(SRCS:.c=.o))
DEPS = $(addprefix obj/, $(SRCS:.c=.d))

RM = rm -rf

all:		folders make_libs $(NAME)

folders:
	mkdir -p obj/tokenize obj/builtins obj/token_expander obj/runner obj/token_loop \
		obj/heredoc_processing obj/io_redirs obj/get_heredocs obj/signals obj/utils


make_libs: $(RL)
	if [ ! -f $(RL)config.status ] ; then \
		cd $(RL) && ./configure ; \
	fi
	$(MAKE) -C $(RL)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(GNL)

$(RL):
	curl $(RL_URL) > $(RL_FILE)
	tar -xf $(RL_FILE) && mv readline-master/ $(RL)
	rm -rf $(RL_FILE)

$(NAME):	$(OBJS) $(LIBFT_A) $(GNL_A) $(RL_A) $(RLHIST_A)
	$(CC) $(CFLAGS) $(DEFS) $(OBJS) $(LIBFT_A) $(GNL_A) $(RL_A) $(RLHIST_A) -L$(RL) -lreadline -ltermcap -o $(NAME)

obj/%.o:	src/%.c Makefile
	$(CC) $(CFLAGS) $(DEFS) -c $< -MMD -o $@

-include $(DEPS)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(GNL)
	$(MAKE) clean -C $(RL)
	$(RM) obj

fclean:
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) fclean -C $(GNL)
	$(MAKE) clean -C $(RL)
	$(RM) obj $(NAME)

re:			fclean all

.PHONY: all clean fclean re
