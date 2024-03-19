# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 16:38:42 by akozin            #+#    #+#              #
#    Updated: 2024/03/19 12:32:33 by akozin           ###   ########.fr        #
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
CFLAGS = -Wall -Wextra -Werror
DEFS = -DREADLINE_LIBRARY

SRCNAMES = main.c

SRCS = $(addprefix src/, $(SRCNAMES))
OBJS = $(SRCS:.c=.o)
DFILES = $(SRCS:.c=.d)

RM = rm -f

all:		make_libs $(NAME)

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

$(NAME):	$(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(DEFS) $(OBJS) -L$(LIBFT) -lft -L$(RL) -I$(RL) -lreadline -lhistory -o $(NAME)

$(OBJS): %.o: %.c Makefile
	$(CC) $(CFLAGS) $(DEFS) -I$(RL) -MMD -MP -c -o $@ $<

-include $(DFILES)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(RL)
	$(RM) $(OBJS) $(DFILES)

fclean:	
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) clean -C $(RL)
	$(RM) $(OBJS) $(DFILES) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
