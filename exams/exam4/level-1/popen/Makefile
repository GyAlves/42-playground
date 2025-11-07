# Program
NAME = program_name

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

# Directories
SRC_DIR = ./
OBJ_DIR = objs/

SRCS = $(wildcard *.c)

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

# Libraries
LIBS = -lpthread

all: $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS) $(LIBS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) ./$(NAME)

re: fclean all

.PHONY: all clean fclean re
