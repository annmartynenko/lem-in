#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amartyne <amartyne@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/18 14:09:45 by amartyne          #+#    #+#              #
#    Updated: 2019/01/18 14:09:46 by amartyne         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

SRC = lem-in.c read_map.c ft_strlnen_chr.c

HDR = lem-in.h get_next_line.h

FLAGS = -Wall -Wextra -Werror

OUT = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c $(HDR)
	gcc $(FLAGS) -o $@ $<

./libft/libft.a:
	make -C libft

$(NAME): $(OUT) ./libft/libft.a
	gcc -o $(NAME) $(FLAGS) -L ./libft -lft -lm  $(SRC)

clean:
	make clean -C libft
	/bin/rm -f *.o

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME)

re: fclean all