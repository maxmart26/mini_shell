# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 07:30:24 by matorgue          #+#    #+#              #
#    Updated: 2024/01/10 15:47:02 by matorgue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBC = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_memset.c ft_strlen.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_substr.c ft_strdup.c \
ft_strjoin.c ft_strtrim.c\
	get_next_line_utils_bonus.c\
	get_next_line_bonus.c
	
ADD = ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
ft_putendl_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_split.c
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
SRCS = ${LIBC} ${ADD}

SRCSALL = ${LIBC} ${ADD} ${BONUS}

OBJS = ${SRCS:.c=.o}

OBJSALL = ${SRCSALL:.c=.o}
.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	ar -rsc ${NAME} ${OBJS}

bonus : ${OBJSALL}
	ar -rsc ${NAME} ${OBJSALL}

all: ${NAME}

clean:
	rm -f ${OBJSALL}

fclean: clean;
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
