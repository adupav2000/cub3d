NAME		= Cub3D_EXE

SRCS		= main.c \


OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CFLAGS		=  -Wall -Werror -Wextra

CC			= gcc

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all:		${NAME}

bonus:		${OBJS}
	${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
