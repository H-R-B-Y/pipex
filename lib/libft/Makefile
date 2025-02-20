
# ███████ ████████  █████  ████████ ██  ██████ 
# ██         ██    ██   ██    ██    ██ ██      
# ███████    ██    ███████    ██    ██ ██      
#      ██    ██    ██   ██    ██    ██ ██      
# ███████    ██    ██   ██    ██    ██  ██████ 


NAME		= libft.a
HEADER		= libft.h

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rc

# Mandatory functions
SRC			= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
			ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			ft_substr.c ft_tolower.c ft_toupper.c ft_memmove.c
# Extra functions
SRC			+= ft_iswhitespace.c ft_splitquoted.c ft_splitfn.c ft_atof.c

# Bonus functions
BSRC		= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
			ft_lstmap_bonus.c ft_lstget_bonus.c
# Extra bonus functions
BSRC		+= ft_lstiter_param_bonus.c

# get next line
GNLDIR		= ft_gnl
GNLSRC		= $(GNLDIR)/get_next_line.c \
			$(GNLDIR)/get_next_line_utils.c

# printf
PRNTDIR		= ft_printf
PRNTSRC		+= $(PRNTDIR)/bitflags.c \
			$(PRNTDIR)/conv_factory.c \
			$(PRNTDIR)/conversion_functions.c \
			$(PRNTDIR)/prefix_padding.c \
			$(PRNTDIR)/ft_printf.c \
			$(PRNTDIR)/general_functions.c \
			$(PRNTDIR)/escape_parsing.c \
			$(PRNTDIR)/precision.c \
			$(PRNTDIR)/generators.c

OBJ			= $(SRC:.c=.o)
BOBJ		= $(BSRC:.c=.o)
GNLOBJ		= $(GNLSRC:.c=.o)
PRNTOBJ		= $(PRNTSRC:.c=.o)

# ██████  ███████  ██████ ██ ██████  ███████ 
# ██   ██ ██      ██      ██ ██   ██ ██      
# ██████  █████   ██      ██ ██████  █████   
# ██   ██ ██      ██      ██ ██      ██      
# ██   ██ ███████  ██████ ██ ██      ███████ 


all:		pre $(NAME) bonus print get_next_line post

$(NAME):	$(OBJ)
			@$(AR) $(NAME) $(OBJ)

.c.o:
			@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

bonus:		$(BOBJ)
			@$(AR) $(NAME) $(BOBJ)

print:		$(OBj) $(PRNTOBJ)
			@$(AR) $(NAME) $(OBJ) $(PRNTOBJ)

get_next_line:	$(OBJ) $(GNLOBJ)
			@$(AR) $(NAME) $(GNLOBJ)

clean:
			@rm -f $(OBJ) $(BOBJ) $(PRNTOBJ) $(GNLOBJ)

fclean:		pre clean post
			@rm -f libft.a libft.so

re:			fclean all

.PHONY:		re all clean fclean bonus

pre:
	@echo
	@echo "   /)  /)",
	@echo " ପ(˶•-•˶)ଓ ♡",
	@echo -n "  /づ  づ ˚₊‧꒰$(NAME) :: $(MAKECMDGOALS) :: Wait  ꒱ ‧₊˚⭒"

post:
	@echo "\b\b\b\b\b\b\b\b\b\b\b\b\bDone  ꒱ ‧₊˚⭒"
	@echo 

# For portable object files
so:
			@$(CC) -nostartfiles -fPIC $(CFLAGS) -c $(SRC) $(BSRC) $(GNLSRC) $(PRNTSRC)
			@gcc -nostartfiles -shared -o libft.so $(OBJ) $(BOBJ) $(GNLOBJ) $(PRNTOBJ)

# ███    ██  ██████  ████████ ███████ 
# ████   ██ ██    ██    ██    ██      
# ██ ██  ██ ██    ██    ██    █████   
# ██  ██ ██ ██    ██    ██    ██      
# ██   ████  ██████     ██    ███████ 

# To include this as a library in your project,
# copy libft to lib folder copy includes to includes folder
# and add the following to your Makefile:

# static vars:
# LIBFT_DIR		:= $(abspath $(LIB_DIR)/libft)
# LIBFT			:= $(LIBFT_DIR)/libft.a

# Recipe:
# $(LIBFT):
# 		$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)"

# for clean:
# $(MAKE) --directory $(LIBFT_DIR) clean

# for fclean:
# $(MAKE) --directory $(LIBFT_DIR) fclean
