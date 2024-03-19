# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 16:38:42 by akozin            #+#    #+#              #
#    Updated: 2024/03/19 11:27:38 by akozin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/
LIBFT_A = $(addprefix $(LIBFT), libft.a)

NAME = minishell

MAKE = make

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCNAMES = 

SRCS = $(addprefix src/, $(SRCNAMES))
OBJS = $(SRCS:.c=.o)
DFILES = $(SRCS:.c=.d)

RM = rm -f

all:		make_libs $(NAME)

make_libs:
	$(MAKE) -C $(LIBFT)

$(NAME):	$(OBJS) $(LIBFT_A)
	$(CC) $(OBJS) -L$(LIBFT) -lft -o $(NAME)

$(OBJS): %.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

-include $(DFILES)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(RM) $(OBJS) $(DFILES)

fclean:	
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(OBJS) $(DFILES)
	$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
