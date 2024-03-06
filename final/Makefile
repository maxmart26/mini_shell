NAME = minishell
INCLUDE = include/minishell_include.h\
		  include/minishell_proto.h\
		  include/minishell_struct.h
OBJ = minishell.c\
	  main.c\
	  init_test.c\
	  utils_bonus2.c\
	  init_data.c\
	  builting.c\
	  echo.c\
	  env.c\
	  cd.c\
	  pwd.c\
	  exec.c\
	  exec_abs.c\
	  unset.c\
	  export.c\
	  ft_lstnew.c\
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
	  srcs/utils/utils.c 
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -lreadline
SRCS = ${OBJ}
OBJS = ${SRCS:.c=.o}
LIBFT_DIR = utilitaire/libft
LIBFT_PATH = utilitaire/libft/libft.a

%.o:%.c ${INCLUDE}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${SRCS} ${LIBFT_PATH}
	make ${OBJS}
	cc ${CFLAGS} ${OBJS} ${LIBFT_PATH} -o ${NAME} ${LDFLAGS}

${LIBFT_PATH}:
				${MAKE} -C ${LIBFT_DIR}

all: ${NAME}

clean:
	${MAKE} -C ${LIBFT_DIR} clean
	rm -f ${OBJS}

fclean: clean;
	${MAKE} -C ${LIBFT_DIR} fclean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re