NAME = parsing
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

LIBFT_DIR = libs/libft
INC_DIR = includes/
SRC_DIR = srcs/
LEX_DIR = srcs/lexer/
PARS_DIR = srcs/parser/

SRC = main.c \
      srcs/lexer/lexer.c \
	  srcs/lexer/get_token.c \
	  srcs/lexer/get_word.c \
	  srcs/parser/parser.c \
	  srcs/lexer/manage_quotes.c

OBJ = ${SRC:.c=.o}
INCLUDES = includes/lexer.h includes/parser.h
LIBFT_DIR = libs/libft
LIBFT_PATH = libs/libft/libft.a

all: ${NAME}

${NAME}: ${OBJ} ${INCLUDES} ${LIBFT_PATH}
	${CC} ${CFLAGS} ${OBJ} ${LIBFT_PATH} -o ${NAME} 

${LIBFT_PATH}:
				${MAKE} -C ${LIBFT_DIR}

clean:
	${MAKE} -C ${LIBFT_DIR} clean
	rm -f ${OBJ}

fclean: clean;
	${MAKE} -C ${LIBFT_DIR} fclean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re