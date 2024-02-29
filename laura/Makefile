NAME = parsing
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -lreadline

LIBFT_DIR = libs/libft
INC_DIR = includes/
SRC_DIR = srcs/
LEX_DIR = srcs/lexer/
PARS_DIR = srcs/parser/

SRC = main.c \
      srcs/lexer/lexer.c \
	  srcs/lexer/get_token.c \
	  srcs/lexer/get_word.c \
	  srcs/lexer/manage_quotes.c \
	  srcs/lexer/manage_sep.c \
	  srcs/lexer/print_lexer.c \
	  srcs/lexer/gather_words.c \
	  srcs/lexer/manage_type.c \
	  srcs/parser/parser.c \
	  srcs/expand/expand.c \
	  srcs/error_handler/ft_error.c \
	  srcs/utils/utils.c \
	  srcs/utils/env.c

OBJ = ${SRC:.c=.o}
INCLUDES = includes/minishell.h includes/lexer.h includes/parser.h includes/error.h
LIBFT_DIR = libs/libft
LIBFT_PATH = libs/libft/libft.a

all: ${NAME}

${NAME}: ${OBJ} ${INCLUDES} ${LIBFT_PATH}
	${CC} ${CFLAGS} ${OBJ} ${LIBFT_PATH} -o ${NAME} ${LDFLAGS}

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