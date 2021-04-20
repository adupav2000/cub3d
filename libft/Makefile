# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 17:38:21 by adu-pavi          #+#    #+#              #
#    Updated: 2021/04/20 21:27:26 by adu-pavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_get_int_char_length.c\
	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_islower.c\
	ft_isprint.c ft_isupper.c ft_itoa.c ft_memdel.c\
	ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c\
	ft_memset.c ft_occure_in_set.c ft_putchar_fd.c ft_putendl_fd.c\
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_str_count_opt.c ft_strchr.c\
	ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
	ft_strlenopt.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c\
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_isspace.c\
	ft_strlenstropt.c ft_strnew.c ft_lstnew.c ft_lstadd_front.c\
	ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
	ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_strcpy.c get_next_line.c



OBJ = $(subst .c,.o,$(SRC))

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
