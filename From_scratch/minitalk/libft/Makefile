# Directories
LIBFT_DIR = .
PRINTF_DIR = ./ft_printf
#******** Source and object FILES ********
SRC = $(addsuffix .c, ft_atoi ft_putchar_fd ft_putstr_fd ft_putnbr_fd ft_strlen ft_isdigit) 
PRINTF_SRCS = $(PRINTF_DIR)/ft_putchar.c $(PRINTF_DIR)/ft_putnbr.c \
			  $(PRINTF_DIR)/ft_putstr.c $(PRINTF_DIR)/put_add.c \
			  $(PRINTF_DIR)/put_hex.c $(PRINTF_DIR)/put_unsigned.c \
			  $(PRINTF_DIR)/upper_hexa.c $(PRINTF_DIR)/printf.c
#******** Object files *************
LIB_OBJS := $(SRC:.c=.o)
PR_OBJS := $(PRINTF_SRCS:.c=.o)
#******** Compiling settings ********
NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I$(PRINTF_DIR)
#********* RULES *********
#
all: $(NAME)
#
$(NAME): $(LIB_OBJS)	$(PR_OBJS)
	ar rcs	$(NAME)	$(LIB_OBJS)	$(PR_OBJS)
#
%.o: %.c
	$(CC)	$(FLAGS)	$(INCLUDES) -c $< -o $@
#
clean:
	rm -f	$(LIB_OBJS)	$(PR_OBJS)
#
fclean: clean
	rm -f	$(NAME)
#
re: fclean	all
#.
.PHONY: all clean fclean re
