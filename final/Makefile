NAME = minishell

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./include

INCLUDES = $(wildcard $(INC_DIR)/*)
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)
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