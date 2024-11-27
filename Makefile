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
				$(SRC_DIR)/validate_files.c

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

# HB_MATH_DIR		:= $(abspath $(LIB_DIR)/hb_math_ext)
# HB_MATH			:= $(HB_MATH_DIR)/hb_math_ext.a
# LIBMLX_DIR		:= $(abspath $(LIB_DIR)/MLX42)
# LIBMLX			:= $(LIBMLX_DIR)/build/libmlx42.a
# LIBFLAGS		:=  -ldl `pkg-config --libs glfw3` -pthread -lm
# $(LIBMLX):
# 		cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make CFLAGS="$(CFLAGS)" -C $(LIBMLX_DIR)/build -j4
# $(HB_MATH):
# 		$(MAKE) --directory $(HB_MATH_DIR) all CFLAGS="$(CFLAGS)"
