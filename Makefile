NAME		= Cub3D_EXE

PARSING_DIR = config
PARSING_SRCS = config/parsing.c config/textures.c config/colors.c\
			   config/map.c engine/raycasting.c engine/event_listener.c\
			   engine/camera.c config/check_function.c config/init_function.c\
			   engine/map_info.c engine/drawing.c config/clear.c screenshot.c

SRCS		= main.c $(PARSING_SRCS) \

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CFLAGS		=  -Wall -Werror -Wextra

CC			= gcc

.c.o:
	${CC} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	gcc -I /opt/X11/include -g -L /opt/X11/lib -l mlx \
			-framework OpenGL -framework AppKit $(SRCS) -lm libft/libft.a  

all:		${NAME}

bonus:		${OBJS}
	${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
