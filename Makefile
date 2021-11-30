# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 13:18:55 by nfaivre           #+#    #+#              #
#    Updated: 2021/11/30 23:23:35 by nfaivre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

NAME = Philosopher

CC = clang
CFLAGS = -Wall -Werror -Wextra

DIR_SRC = src
DIR_OBJ = .obj

INCLUDE = -Iinclude

SRC = $(wildcard $(DIR_SRC)/*.c)
OBJ = $(addprefix $(DIR_OBJ)/, $(notdir $(SRC:.c=.o)))

mkdir_DIR_OBJ:
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c ./include/header.h
	@mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lpthread

all: mkdir_DIR_OBJ $(OBJ) $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(DIR_OBJ)

re: fclean all

.PHONY: all clean fclean re
