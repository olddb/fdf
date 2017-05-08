# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/17 23:21:27 by vpailhe           #+#    #+#              #
#    Updated: 2015/03/11 18:07:53 by vpailhe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

SRC = draw.c\
	  get_next_line.c\
	  l_funcs.c\
	  main.c\
	  parsing.c\
	  struct_maker.c\
	  fill.c\

OBJ = draw.o\
	  get_next_line.o\
	  l_funcs.o\
	  main.o\
	  parsing.o\
	  struct_maker.o\
	  fill.o\

FLAG = -Wall -Wextra -Werror

LIB = /usr/X11/lib -lmlx -lXext -lX11 -lm

INC = -I /usr/X11/include/X11

.PHONY : libft.a

all : libft.a $(NAME)

libft.a:
	@$(MAKE) -C ./libft

$(OBJ):
	gcc -c $(SRC) libft/libft.a -L $(LIB) -I ./libft/includes

#	gcc $(FLAG) -c $(SRC) libft/libft.a -L $(LIB) -I ./libft/includes

$(NAME): $(OBJ)
	gcc $(OBJ) libft/libft.a -L $(LIB) -I ./libft/includes -o $(NAME)

%.o: %.c
	gcc -I ./libft/includes -c $@ $^ 

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
