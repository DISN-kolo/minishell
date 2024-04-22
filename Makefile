# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 16:38:42 by akozin            #+#    #+#              #
#    Updated: 2024/04/22 12:32:38 by akozin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/
LIBFT_A = $(addprefix $(LIBFT), libft.a)

RL = readline/
RL_A = $(addprefix $(RL), libreadline.a)
RLHIST_A = $(addprefix $(RL), libhistory.a)
RL_URL = http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz
RL_FILE = readline-master.tar.gz

NAME = minishell

MAKE = make

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
DEFS = -DREADLINE_LIBRARY

SRCNAMES = main.c \
			shell_loop.c \
			tokenize/tokenize.c \
			tokenize/tokenize_count.c \
			tokenize/tokenize_split.c \
			tokenize/tokenize_err_probe.c \
			get_heredocs.c \
			heredoc_processing/heredoc_rl.c \
			token_loop/token_loop.c \
			token_loop/token_loop_utils.c \
			token_loop/cmd_loop.c \
			token_loop/cmd_filler.c \
			token_loop/cmd_filler_utils.c \
			token_expander/token_expander.c \
			token_expander/token_expander_utils.c \
			token_expander/token_expander_utils_2.c \
			token_expander/dollar_expander.c \
			token_expander/new_token_splitter.c \
			token_expander/new_token_splitter_utils.c \
			expand_vars.c \
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
			enviroment.c \
			free_utils.c

SRCS = $(SRCNAMES)
OBJS = $(addprefix obj/, $(SRCS:.c=.o))
DEPS = $(addprefix obj/, $(SRCS:.c=.d))

RM = rm -rf

all:		folders make_libs $(NAME)

folders:
	mkdir -p obj/tokenize obj/builtins obj/token_expander obj/runner obj/token_loop \
		obj/heredoc_processing


make_libs: $(RL)
	if [ ! -f $(RL)config.status ] ; then \
		cd $(RL) && ./configure ; \
	fi
	$(MAKE) -C $(RL)
	$(MAKE) -C $(LIBFT)

$(RL):
	curl $(RL_URL) > $(RL_FILE)
	tar -xf $(RL_FILE) && mv readline-master/ $(RL)
	rm -rf $(RL_FILE)

$(NAME):	$(OBJS) $(LIBFT_A) $(RL_A) $(RLHIST_A)
	$(CC) $(CFLAGS) $(DEFS) $(OBJS) $(LIBFT_A) $(RL_A) $(RLHIST_A) -L$(RL) -lreadline -ltermcap -o $(NAME)

obj/%.o:	src/%.c Makefile
	$(CC) $(CFLAGS) $(DEFS) -c $< -MMD -o $@

-include $(DEPS)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(RL)
	$(RM) obj

fclean:
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) clean -C $(RL)
	$(RM) obj $(NAME)

re:			fclean all

.PHONY: all clean fclean re
