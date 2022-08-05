# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 00:42:56 by atoullel          #+#    #+#              #
#    Updated: 2022/07/23 06:01:42 by atoullel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME =          pipex

EXECUTABLE =	pipex

CC =            gcc

CFLAGS =		-Wall -Wextra -Werror

INCLUDE_PATH =  includes/

# \*----- SRC OBJ -----*/
SRC_DIR = src/

SRC =	child.c\
		free.c\
		pipex.c\
		error.c\

SRC_OBJ = ${addprefix $(SRC_DIR), $(SRC:.c=.o)}

# \*----- UTILS OBJ -----*/

UTILS_DIR = utils/

UTILS =	ft_split.c \
		ft_strjoin.c \
		ft_strncmp.c \
		ft_strlen.c \
		
UTILS_OBJ = ${addprefix $(UTILS_DIR), $(UTILS:.c=.o)}
	
all: $(NAME)

$(NAME):	$(SRC_OBJ) $(UTILS_OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(SRC_OBJ) $(UTILS_OBJ) -I $(INCLUDE_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -o $@ -c $<

clean:
				${RM} ${SRC_OBJ}
				${RM} ${UTILS_OBJ}

fclean:
				${RM} ${UTILS_OBJ}
				${RM} ${SRC_OBJ}
				rm -f ${NAME}

re:         	fclean all

.PHONY:        all clean fclean re
