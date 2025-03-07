NAME			:= pipex
CFLAGS			:= -Wextra -Wall -Werror -g3 -O0

HEADERS			:= -I ./include

LIB_DIR			:= ./lib

LIBFT_DIR		:= $(abspath $(LIB_DIR)/libft)
LIBFT			:= $(LIBFT_DIR)/libft.a

SRC_DIR			:= ./src
SRCS			:= $(SRC_DIR)/get_cmd.c \
				$(SRC_DIR)/stack_handler.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/validate_files.c \
				$(SRC_DIR)/handle_heredoc.c \
				$(SRC_DIR)/cleanup.c

OBJS			:= ${SRCS:.c=.o}

MAIN			:= $(SRC_DIR)/main.c

all: $(NAME)

$(LIBFT):
		$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)"

.c.o:
		$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)


$(NAME): $(MAIN) $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(MAIN) $(OBJS) $(LIBFT) -o $(NAME)

clean:
		$(MAKE) --directory $(LIBFT_DIR) clean
		rm -rf $(OBJS)

fclean: clean
		$(MAKE) --directory $(LIBFT_DIR) fclean
		rm -rf $(NAME)

rm:
		rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, test

