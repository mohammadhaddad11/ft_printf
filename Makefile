# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddad <mhaddad@learner.42.tech>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 09:48:44 by mhaddad           #+#    #+#              #
#    Updated: 2026/01/08 12:20:50 by mhaddad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME		= libftprintf.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		= ft_printf.c ft_utils.c ft_print_hex.c ft_print_ptr.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
