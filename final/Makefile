NAME = minishell

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./include

INCLUDES = include/minishell_include.h include/minishell_proto.h include/minishell_struct.h include/libft/libft.h

SRCS = srcs/main.c\
		srcs/error_handler/ft_error.c  srcs/error_handler/ft_free.c \
		srcs/exec/minishell.c srcs/exec/tmp.c \
		srcs/exec/builting/builting.c srcs/exec/builting/cd.c srcs/exec/builting/echo.c srcs/exec/builting/env.c \
		srcs/exec/builting/exit.c srcs/exec/builting/export.c srcs/exec/builting/pwd.c srcs/exec/builting/unset.c srcs/exec/builting/export_2.c \
		srcs/exec/execution/exec_abs.c srcs/exec/execution/exec.c srcs/exec/execution/utils_bonus2.c srcs/exec/execution/dup2.c \
		srcs/exec/herdoc/herdoc.c \
		srcs/exec/init/init_data.c srcs/exec/init/token_init.c srcs/exec/init/init_path.c\
		srcs/expand/expand.c  \
		srcs/exec/init/open_fd.c\
		srcs/exec/init/init_data_env.c\
		srcs/lexer/cmd_args.c srcs/lexer/cmd_args2.c srcs/lexer/cmdbuilt_args.c srcs/lexer/gather_words.c srcs/lexer/get_token.c \
		srcs/lexer/get_word.c srcs/lexer/lexer.c srcs/lexer/manage_quotes.c srcs/lexer/manage_quotes2.c srcs/lexer/manage_sep.c \
		srcs/lexer/manage_type.c srcs/lexer/manage_type2.c srcs/lexer/print_lexer.c \
		srcs/parser/parser.c  \
		srcs/utils/free.c srcs/utils/manage_env.c srcs/utils/newline.c srcs/utils/signals.c srcs/utils/utils.c srcs/utils/utils2.c \
		srcs/utils/utils3.c

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
	
CC = cc
CFLAGS =  -g3  -Wextra -Werror -Wall
LDFLAGS = -lreadline
LIB = ${INC_DIR}/libft/libft.a

%.o:%.c ${INCLUDES}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME} ${LIB}

${LIB}:
	@echo "$(GREEN)Compiling libft : $(NC)"
	@make -s -C ${INC_DIR}/libft/ all
	@echo "\033[32m[✓] libft succesfully compiled\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c $(INCLUDES) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/*/%.c $(INCLUDES) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ) ${LIB}
	@$(CC) $(CFLAGS) $(OBJ) -L$(INC_DIR)/libft -lft -lreadline -o $(NAME)
	@echo "\033[32m[✓] minishell succesfully compiled\033[0m"

clean:
	@$(RM) -r $(OBJ_DIR)
	@make -s -C ${INC_DIR}/libft/ clean

fclean: clean
	@$(RM) $(NAME)
	@make -s -C ${INC_DIR}/libft/ fclean

re: fclean all

.PHONY: all clean fclean re