NAME		= Cub3D_EXE

SRCS		= main.c parsing.c \


OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CFLAGS		=  -Wall -Werror -Wextra

CC			= gcc

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

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
