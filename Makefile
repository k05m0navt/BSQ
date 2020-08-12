# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cillaoi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/12 22:08:43 by cillaoi           #+#    #+#              #
#    Updated: 2020/08/12 22:08:54 by cillaoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

SRC = funcs.c bsq.c utils.c utils2.c

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror $(SRC) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
