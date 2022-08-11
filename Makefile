# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 14:48:49 by ncaba             #+#    #+#              #
#    Updated: 2022/08/11 02:46:24 by atoullel         ###   ########.fr        #
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
				exit.c \
				export.c \
				pwd.c \
				unset.c \

UTILS_SRCS	=	str_utils.c \
				str_utils_2.c \
				split_command.c \
				multi_line.c \
				init.c \
				lst_arg.c \
				mini_signal.c \
				extra_fun.c \

ENV_SRCS	=	env_free.c \
				env_list.c \
				env_util.c \

PIP_SRCS	=	child.c \
				free.c \
				pipex.c \
				error.c \
				utils.c \
				utils2.c \
				utils3.c \

SRC			=	$(addprefix ./srcs/, $(SRCS)) \
				$(addprefix ./srcs/utils/, $(UTILS_SRCS)) \
				$(addprefix ./srcs/env/, $(ENV_SRCS)) \
				$(addprefix ./srcs/builtins/, $(BUILT_SRCS)) \
				$(addprefix ./srcs/pipex/, $(PIP_SRCS))
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
		--track-origins=yes \
		./$(NAME)

re: clean $(NAME)

nonorm: clean $(NAME)

.PHONY: re fclean clean all norminette vtest
