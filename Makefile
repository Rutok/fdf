# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboste <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 23:43:17 by nboste            #+#    #+#              #
#    Updated: 2016/12/09 00:20:43 by nboste           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
FLG = -Wall -Wextra -Werror
SRC = srcs/main.c \
	  srcs/ft_fdf.c \
	  srcs/ft_fdf_hooks.c \

OBJ = $(SRC:%.c=%.o)
FRM = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	make -C ./libft fclean && make -C ./libft
	$(CC) $(FLG) $(SRC) -I./includes/ -I./libft/includes -L./libft -lft -lmlx $(FRM) -o $(NAME)

clean:
	make -C ./libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: re

.SILENT: clean fclean all $(NAME) $(OBJ)
