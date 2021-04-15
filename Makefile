NAME		= Cub3d_EXE

PARSING_SRCS	= config/parsing.c\
					config/textures.c\
					config/colors.c\
					config/map.c\
					engine/raycasting.c\
					engine/event_listener.c\
					engine/camera.c\
					config/check_function.c\
					config/init_function.c\
					engine/map_info.c\
					engine/drawing.c\
					config/clear.c\
					config/clear_2.c\
					screenshot.c\
					engine/sprites.c

SRCS		= main.c $(PARSING_SRCS) \

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CFLAGS		=  -Wall -Werror -Wextra

CC			= gcc

INC			= /usr/include
HT			= Linux
DOCP		= do_cp
.c.o:
	${CC} -c $< -o ${<:.c=.o}

INCLIB 		= $(INC)/../lib

all:		${NAME}

${NAME}:	${OBJS}
	$(CC) -o $(NAME) $(OBJS) -lm libft/libft.a -L. -lm mlx/libmlx.a -L$(INCLIB) -lXext -lX11 -lbsd 

bonus:		${OBJS}
	${NAME} ${OBJS}

clean:
	${RM} ${OBJS}
	${RM} screenshot.bmp

fclean:		clean
	${RM} ${NAME}
	@rm	-f screenshot.bmp

re:			fclean all

.PHONY:		all clean fclean re
