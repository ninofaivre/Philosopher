# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 13:18:55 by nfaivre           #+#    #+#              #
#    Updated: 2021/11/22 13:39:50 by nfaivre          ###   ########.fr        #
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
OBJ = $(addprefix $(DIR_OBJ)/, $(subst src/,, $(SRC:.c=.o)))

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c ./include/header.h
	@mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lpthread $(OBJ) $(GNL_OBJ) -o $(NAME)

all: $(OBJ) $(NAME)

clean:
	@rm -rf $(OBJ)
	@echo "removing $(OBJ)"

fclean: clean
	@rm -rf $(NAME)
	@echo "removing $(NAME)"

re: fclean all

.PHONY: all clean re fclean
