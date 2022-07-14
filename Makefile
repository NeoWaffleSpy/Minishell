# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 14:48:49 by ncaba             #+#    #+#              #
#    Updated: 2022/07/14 20:36:18 by ncaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= clang
CFLAGS		= -Wall -Wextra -Werror
INC			= -I . -I ./include/libft/include/ -L ./include/libft/ -lft -lreadline

SRCS		=	minishell.c \
				sys_call.c \
				builtins.c \
				line_checker.c \

BUILT_SRCS	=	cd.c \
				echo.c \
				env.c \
				export.c \
				pwd.c \
				unser.c \

UTILS_SRCS	=	str_utils.c \
				multi_line.c \

SRC			=	$(addprefix ./srcs/, $(SRCS)) \
				$(addprefix ./srcs/utils/, $(UTILS_SRCS))
#				$(addprefix ./srcs/builtins/, $(BUILT_SRCS))
OBJ			=	$(SRC:.c=.o)

HEADERFILES	=	minishell.h
HEADERS		=	$(addprefix -I ./include/, $(HEADERFILES))

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

norminette:
	@echo -n "\033[31m"
	@norminette | { grep -s Error || echo "\033[32mNo norm errors"; }
	@echo -n "\033[0m"

vtest: $(NAME)
	valgrind \
		--leak-check=full \
		--track-fds=yes \
		--show-leak-kinds=all \
		--suppressions=.ignore_readline \
		./$(NAME)

re: clean norminette $(NAME) vtest

nonorm: clean $(NAME)

.PHONY: re fclean clean all norminette vtest
