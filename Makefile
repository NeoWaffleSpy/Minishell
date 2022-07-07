# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 14:48:49 by ncaba             #+#    #+#              #
#    Updated: 2022/07/07 17:46:55 by ncaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= clang
CFLAGS		= -Wall -Wextra -Werror
INC			= -I . -I ./include/libft/include/ -L ./include/libft/ -lft -lreadline

SRCS		=	minishell.c \
				sys_call.c

SRC			= $(addprefix ./srcs/, $(SRCS))
OBJ			= $(SRC:.c=.o)

HEADERFILES	=	minishell.h
HEADERS		= $(addprefix -I ./include/, $(HEADERFILES))

LIBFT		= ./include/libft/libft.a

all: $(NAME)
	@echo "Compiled !"

$(LIBFT):
	@make -s -C ./include/libft/

$(NAME): $(LIBFT) $(OBJ) 
	@$(CC) $(OBJ) $(CFLAGS) $(INC) -o $(NAME) -g

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf a.out.dSYM
	@make -s clean -C ./include/libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make -s fclean -C ./include/libft/

re: clean $(NAME)

.PHONY: re fclean clean all bonus
