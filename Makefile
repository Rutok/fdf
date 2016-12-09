# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboste <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 23:43:17 by nboste            #+#    #+#              #
#    Updated: 2016/12/09 04:53:18 by nboste           ###   ########.fr        #
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

.PHONY: re

.SILENT: clean fclean all $(NAME) $(OBJ)
