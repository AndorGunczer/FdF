# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/24 14:24:34 by agunczer          #+#    #+#              #
#    Updated: 2021/09/23 15:30:26 by agunczer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB= fdflib.a
CC_FLAGS= -Wall -Wextra -Werror
CC= gcc
#COMPILE WITH make MAP=MAPNAME#

all: fdflib.a

fdflib.a:
	make -C ./libft
	make gnl -C ./libft
	make -C ./mlx
	${CC} ${CC_FLAGS} -ferror-limit=500 -c sources/*.c
	mv *.o sources/
	ar -rc sources/fdf.a sources/*.o
	gcc -ferror-limit=50 sources/fdf.a libft/libft.a mlx/libmlx.a -framework OpenGL -framework AppKit -o fdf
	./fdf maps/${MAP}

# %.o: %.c
# 	gcc -Wall -Wextra -Werror -c $< -o $@
# 	make -C mlx/make

clean:
	rm libft/*.o
	rm mlx/*.o
	rm sources/*.o

fclean: clean
	rm mlx/libmlx.a
	rm libft/libft.a
	rm sources/fdf.a
