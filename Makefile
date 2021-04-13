# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 20:15:44 by bbetsey           #+#    #+#              #
#    Updated: 2021/04/11 00:35:29 by bbetsey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT
DIR_HEADERS	=	includes/
DIR_SRCS	=	srcs/
MLX			=	mlx/libmlx.a
MLX_FLAGS	=	-Lmlx -lmlx -framework OpenGL -framework AppKit

SRC			=	main.c\
				\
				rt/rt.c\
				rt/intersect.c\
				rt/sphere.c\
				rt/plane.c\
				rt/triangle.c\
				rt/square.c\
				rt/cylinder.c\
				rt/light.c\
				rt/thread.c\
				\
				utils/atoi.c\
				utils/atof.c\
				utils/error.c\
				utils/split.c\
				utils/strcmp.c\
				utils/print.c\
				utils/print_obj.c\
				utils/free.c\
				utils/arr_len.c\
				utils/check_scene.c\
				utils/other.c\
				utils/color.c\
				utils/rotate.c\
				utils/vector.c\
				utils/vector2.c\
				utils/hooks.c\
				utils/bmp.c\
				\
				parser/parser.c\
				parser/resolution.c\
				parser/ambient.c\
				parser/camera.c\
				parser/light.c\
				parser/sphere.c\
				parser/plane.c\
				parser/cylinder.c\
				parser/square.c\
				parser/triangle.c\
				\
				gnl/get_next_line.c\
				gnl/get_next_line_utils.c\

SRCS		=	${addprefix ${DIR_SRCS}, ${SRC}}
OBJS		=	${SRCS:.c=.o}

all		:		${NAME}

${NAME}	:		${OBJS}
				@make -C mlx/
				@gcc -Wall -Wextra -Werror -I ${DIR_HEADERS} -c srcs/utils/check_res.c
				@gcc -Wall -Wextra -Werror ${MLX_FLAGS} -I ${DIR_HEADERS} ${MLX} check_res.o ${OBJS} -o ${NAME} -pthread
				@echo && echo "\033[1m\033[32m» Assembled ⚑\033[0m" && echo

macos	:		${OBJS}
				@make -C mlx/
				@gcc -Wall -Wextra -Werror -I ${DIR_HEADERS} -c srcs/utils/check_res_lim.c
				@gcc -Wall -Wextra -Werror ${MLX_FLAGS} -I ${DIR_HEADERS} ${MLX} ${OBJS} check_res_lim.o -o ${NAME} -pthread
				@echo && echo "\033[1m\033[32m» Assembled ⚑\033[0m" && echo

%.o		: 		%.c
				@gcc -Wall -Wextra -Werror -I ${DIR_HEADERS} -c $< -o $@

norm	:
				@norminette $(DIR_SRCS) includes/get_next_line.h includes/minirt.h includes/parse.h includes/utils.h includes/vector.h includes/rt.h

clean	:
				@rm -rf ${OBJS} && rm -f check_res.o check_res_lim.o && rm -f img.bmp

fclean	:		clean
				@rm -f ${NAME}

re		:		fclean all

bonus	:		all

.PHONY	:		all, clean, fclean, re, bonus

leaks	:		re
				@valgrind ./miniRT example.rt --leak-check=full
				@rm -rf ${OBJS} objs_dir ${NAME} miniRT.dSYM
