# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboste <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 23:43:17 by nboste            #+#    #+#              #
#    Updated: 2016/12/10 01:26:04 by nboste           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
FLG = -Wall -Wextra -Werror
SRC = srcs/main.c \
	  srcs/ft_fdf.c \
	  srcs/ft_fdf_hooks.c \
	  srcs/ft_fdf_error.c \
	  srcs/ft_fdf_reader.c \
	  srcs/ft_fdf_drawer.c \
	  srcs/ft_fdf_process.c \

OBJ = $(SRC:%.c=%.o)
MLX = -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	make -C ./libft
	$(CC) $(FLG) $(SRC) -I./includes/ -I./libft/includes -L./libft -lft $(MLX) -o $(NAME)

clean:
	make -C ./libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

rex: fclean all
	./$(NAME) 1000 1000

.PHONY: re

.SILENT: clean fclean all $(NAME) $(OBJ)
