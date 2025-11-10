# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 14:34:10 by cdohanic          #+#    #+#              #
#    Updated: 2025/08/30 19:36:45 by cdohanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes
LDLIBS = -lpthread

SRC_DIR = src
OBJ_DIR = object

MAIN_FILES = philos.c sim_start.c philo_routine.c parse.c utils.c

# SRC =   $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

SRC = $(addprefix $(SRC_DIR)/, $(MAIN_FILES))

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDLIBS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
