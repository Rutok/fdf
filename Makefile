# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboste <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 23:43:17 by nboste            #+#    #+#              #
#*   Updated: 2017/03/15 14:11:13 by nboste           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
FLG = -Wall -Wextra -Werror
SRC = srcs/main.c \
	  srcs/fdf.c \
	  srcs/fdf_reader.c \
	  srcs/fdf_drawer.c \
	  srcs/fdf_process.c \
	  srcs/fdf_matrix.c \
	  srcs/fdf_event.c \

OBJ = $(SRC:%.c=%.o)

INC = -I./includes \
	  -I./engine/includes \
	  -I./engine/libft/includes \
	  -I/usr/includes\
	  -I/Library/Frameworks/SDL2.framework/Headers

LIB = -L./engine \
	  -L./engine/libft \
	  -I/Library/Frameworks/SDL2.framework/ \

all: $(NAME)

$(NAME):
	make -C ./engine
	$(CC) $(FLG) $(LIB) $(INC) $(SRC) -lm -lengine -lft -framework SDL2 -o $(NAME) -O3

linux:
	make -C ./engine
	$(CC) $(FLG) $(LIB) $(INC) $(SRC) -lm -lengine -lft -lSDL2 -o $(NAME) -O3

linuxd:
	make -C ./engine
	$(CC) $(FLG) $(LIB) $(INC) $(SRC) -lm -lengine -lft -lSDL2 -o $(NAME) -g -pg

clean:
	make -C ./engine clean
	rm -rf $(OBJ)

fclean: clean
	make -C ./engine fclean
	rm -rf $(NAME)

debug:
	make -C ./engine
	$(CC) $(FLG) $(LIB) $(INC) $(SRC) -lm -lengine -lft -framework SDL2 -o $(NAME) -g

re: fclean all

rex: fclean all
	./$(NAME) maps/t2.fdf 
