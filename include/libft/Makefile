# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 14:48:49 by ncaba             #+#    #+#              #
#    Updated: 2022/07/26 20:41:50 by ncaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror -g3
LFTFILES =	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_cpy_tab.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_itoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_switch.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_free_all_bonus.c \
			ft_pow_bonus.c \
			ft_putchar_bonus.c \
			ft_putendl_bonus.c \
			ft_putnbr_bonus.c \
			ft_putstr_bonus.c \
			ft_realloc_bonus.c \
			ft_return0_bonus.c \
			ft_strcat_bonus.c \
			ft_strcpy_bonus.c
PFFILES =	ft_printf.c \
			ft_parse.c \
			ft_convert_hexa.c \
			ft_convert_int.c \
			ft_convert_percent.c \
			ft_convert_pointer.c \
			ft_convert_string.c \
			ft_convert_unsigned.c \
			ft_convert_char.c \
			ft_multiflag.c \
			ft_flags_sorter.c \
			ft_spacing.c \
			ft_itoa_base.c
GNLFILES =	get_next_line.c
GARFILES =	garbage_collector.c
SRCSDIR = ./srcs/
SRCS =	$(addprefix $(SRCSDIR)libft/, $(LFTFILES)) \
		$(addprefix $(SRCSDIR)ft_printf/, $(PFFILES)) \
		$(addprefix $(SRCSDIR)get_next_line/, $(GNLFILES)) \
		$(addprefix $(SRCSDIR)garbage_collec/, $(GARFILES))
OBJS = $(SRCS:.c=.o)
HEADERS = 	libft.h \
			ft_printf.h \
			get_next_line.h \
			ft_lib.h
HEADDIR = ./include/
HEADERFLAGS = $(addprefix -I $(HEADDIR), $(HEADERS))

all: $(NAME)
	@echo "Compiled libft !"

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS) 
	@ranlib $(NAME)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) $(HEADERFLAGS) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJS) $(OBJTEST)
	@/bin/rm -rf a.out.dSYM
	@/bin/rm -f libft.gch

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean $(NAME)

.PHONY: re fclean clean all maintest bonus retest
