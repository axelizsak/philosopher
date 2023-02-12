# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aizsak <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 05:10:35 by aizsak            #+#    #+#              #
#    Updated: 2023/02/12 08:24:46 by aizsak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src

BIN_DIR = bin/

SRC =	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parsing.c \
	$(SRC_DIR)/action.c \
	$(SRC_DIR)/action1.c \
	$(SRC_DIR)/utils1.c \
	$(SRC_DIR)/utils.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)%.o)

INCLUDES = ./includes

CFLAGS = -Wall -Werror -Wextra -pthread -I$(INCLUDES)

all :	$(BIN_DIR) $(NAME)

$(OBJ) :	 $(BIN_DIR)%.o: $(SRC_DIR)/%.c
		@ $(CC) -I$(INCLUDES) -c $< -o $@

$(NAME) :	$(BIN_DIR) $(OBJ)
			@ $(CC) $(CFLAGS) $(OBJ) -o $(NAME)
			@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

$(BIN_DIR) :
		@ mkdir -p $(BIN_DIR)

clean :
		@ rm -f $(OBJ)
		@ rm -rf $(BIN_DIR)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove binary files .. 🧹"

fclean : clean
		@ rm -f $(NAME)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove executable .. 🗑️"

re :
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRecompile .. 🔄"
	@ $(MAKE) -s fclean all

.PHONY: all clean fclean re
