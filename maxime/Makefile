NAME = minishell
INCLUDE = include/minishell_include.h\
		  include/minishell_proto.h\
		  include/minishell_struct.h
OBJ = minishell.c
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
SRCS = ${OBJ}
OBJS = ${SRCS:.c=.o}

%.o:%.c ${INCLUDE}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${SRCS}
	make ${OBJS}
	cc ${CFLAGS} ${OBJS} -o ${NAME} 

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean;
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re