NAME		= Cub3D_EXE

PARSING_DIR = config
PARSING_SRCS = config/parsing.c config/textures.c config/colors.c\
			   config/map.c engine/raycasting.c engine/event_listener.c\
			   engine/camera.c config/check_function.c config/init_function.c\
			   engine/map_info.c engine/drawing.c config/clear.c screenshot.c

SRCS		= main.c $(PARSING_SRCS) \

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			=  -Wall -Wextra -Werror -I.
LIBS			= -framework OpenGL -framework AppKit -lm libft/libft.a -L. -lmlx
MLX				= libmlx.dylib

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
				$(MAKE) -C mlx
				mv mlx/$(MLX) .

clean:
				$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
