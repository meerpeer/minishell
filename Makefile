NAME = minishell
CFLAGS ?= -Wall -Wextra -Werror #-g -fsanitize=address
CC = gcc

INC = includes
HEADERFILES = minishell.h

SRC_FILES = main.c prompt.c\
			initialize/init_mini_data.c\
			executor/execute.c executor/execute_redirection.c executor/execute_wait.c\
			executor/execute_utils.c executor/execute_path.c executor/execute_filehandler.c\
			builtins/cd_builtin.c builtins/echo_builtin.c builtins/env_builtin.c\
			builtins/exit_builtin.c builtins/export_builtin.c\
			builtins/pwd_builtin.c builtins/unset_builtin.c\
			environment/env_gets.c environment/env_change.c environment/env_utils.c\
			error/error.c\
			utils/free_data.c utils/string_utils.c\
			lexer/lexer_utils.c lexer/lexer.c lexer/split_utiles.c lexer/print_list.c\
			lexer/token_utils.c lexer/split_for_tokens.c\
			parsing/parse_print.c parsing/parse_redirect.c parsing/parse.c parsing/parse_word.c\
			parsing/parse_expand.c parsing/parse_quote.c parsing/parse_heredoc.c\
			signals/signals.c

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix obj/, $(OBJ_FILES))

LIB += libft/libft.a
LIB += -lreadline  -L `brew --prefix readline`/lib #-lhistory
LIBFT_DIR = libft/

#-------------------------------------------#
BLUE			=	\033[38;5;30m
GREEN			= 	\033[38;5;43m
RED				=	\033[38;5;124m
PINK			= 	\033[38;5;167m
ORANGE			=	\033[38;5;208m
NO_COLOR		=	\033[0m
#-------------------------------------------#

all: start $(NAME)

start:
		@echo "\033[38;5;210m 🐌The Operating Systers 🐚 present:\033[0m"
		@echo "\033[38;5;42m\t╔╦╗╦╔╗╔╦╔═╗╦ ╦╔═╗╦  ╦\033[0m"
		@echo "\033[38;5;43m\t║║║║║║║║╚═╗╠═╣║╣ ║  ║\033[0m"  
		@echo "\033[38;5;44m\t╩ ╩╩╝╚╝╩╚═╝╩ ╩╚═╝╩═╝╩═╝\033[0m"
		@echo "\033[38;5;25m\t    WE SHALL BASH!\033[0m"
$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS)  $(OBJS) $(LIB) -o $(NAME)

obj/%.o: src/%.c $(INC)/$(HEADERFILES)
	@mkdir -p obj/$(dir $*)
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@ -I $(INC) -I `brew --prefix readline`/include

clean:
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
		@echo "\033[38;5;118m 🐌The Operating Systers 🐚 thank you for using:\033[0m"
		@echo "\033[38;5;64m\t╔╦╗╦╔╗╔╦╔═╗╦ ╦╔═╗╦  ╦\033[0m"
		@echo "\033[38;5;65m\t║║║║║║║║╚═╗╠═╣║╣ ║  ║\033[0m"  
		@echo "\033[38;5;66m\t╩ ╩╩╝╚╝╩╚═╝╩ ╩╚═╝╩═╝╩═╝\033[0m"
		@echo "\033[38;5;230m\t    WE SHALL BASH!\033[0m"

re: fclean all

.PHONY: clean fclean re play