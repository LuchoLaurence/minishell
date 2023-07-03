CC = @gcc
CFLAGS = -Wall -Wextra -Werror -I ./srcs/minishell.h -fsanitize=address -g
RM = @rm -rf
LIB_DIR = ./utils/libft
LIB = libft.a
NAME = minishell

UTL_DIR =	utils
UTL_FILES =	\
			ft_split_add_slash.c \
			ft_split_envp.c \
			minisplit.c \
			node_add_back.c \
			node_remove.c
UTL =	$(addprefix $(UTL_DIR)/, $(UTL_FILES))

SRC_DIR =	./srcs
SRC_FILES =	\
			builtin.c \
			change_env.c \
			close_all_previous_files.c \
			echo.c \
			env.c \
			error.c \
			exec.c \
			exec2.c \
			exit.c \
			expander.c \
			export.c \
			export2.c \
			export3.c \
			free.c \
			free2.c \
			find_built_in.c \
			ft_struct_init.c \
			envp_list_to_tab_string.c \
			get_last_infile.c \
			lexer.c \
			main.c \
			open_files_get_fds.c \
			open_here_doc.c \
			unset.c \
			wait_all_processes.c
SRC =	$(UTL) $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = ./objs
OBJ =	$(addprefix $(OBJ_DIR)/, $(UTL:.c=.o)) $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))


all: $(OBJ_DIR)/$(UTL_DIR) $(NAME)

$(OBJ_DIR)/$(UTL_DIR):
	@mkdir -p $@

$(NAME): $(OBJ) $(LIB_DIR)/$(LIB)
	@echo "Compiling Executable"
	$(CC) $(CFLAGS) $(LIB_DIR)/$(LIB) -g -o $(NAME) $(OBJ) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(UTL_DIR)/%.o: $(UTL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/$(LIB):
	@make -C $(LIB_DIR)

clean:
	@echo "Removing Objects"
	$(RM) $(OBJ) $(OBJ_DIR)

fclean: clean
	@echo "Removing Executable"
	$(RM) $(NAME)
	@make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re
