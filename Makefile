NAME			= pipex

MAIN			= main.c

SRC				= 

OBJ				= $(SRC:.c=.o)
LIBFT_DIR		= libft
LIBFT			= libft/libft.a

HEADER			= pipex.h

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -O0


# All target
all:			$(NAME) Makefile $(HEADER)

# Compile objects for named sources.
.c.o:
		
		$(CC) $(CFLAGS) -c $< 

# Compile IDK something, i dont think we need to compile this one LOL
$(NAME):		$(MAIN) $(OBJ) $(LIBFT)
		
		$(CC) $(CFLAGS) $(MAIN) $(OBJ) $(LIBFT) -o $(NAME)


# Compile LIBFT dependency
$(LIBFT):
		
		$(MAKE) --directory $(LIBFT_DIR)

# Clean
clean:
		
		$(MAKE) --directory $(LIBFT_DIR) clean
		rm -f *.o
		rm -f libft.a

# Full Clean
fclean:			clean
		
		$(MAKE) --directory $(LIBFT_DIR) fclean
		rm -f $(NAME)
		rm -f libft.a

# Relink
re:				fclean all

# Phony Targets don't produce a named target.
.PHONY:			fclean clean all re test quicktest