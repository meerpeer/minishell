NAME = minishell
CFLAGS ?= -Wall -Wextra -Werror
CC = gcc

INC = includes
HEADERFILES = minishell.h

SRC_FILES = main.c \
			executor/execute.c executor/redirection.c \
			error/error.c \

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix obj/, $(OBJ_FILES))

LIB += libft/libft.a
LIB += -lreadline #-lhistory
LIBFT_DIR = libft/

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS)  $(OBJS) $(LIB) -o $(NAME)

obj/%.o: src/%.c $(INC)/$(HEADERFILES)
	@mkdir -p obj/$(dir $*)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re play