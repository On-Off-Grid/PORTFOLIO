SRC = $(addsuffix .c, ft_putchar ft_putnbr  ft_putstr  printf  put_add  put_hex  put_unsigned  upper_hexa)
OBJS := $(SRC:.c=.o)
NAME = libftprintf.a
CC = cc
FLAGS = -Wall -Wextra -Werror
INC_DIR = .
DIR_FLAG = -I$(INC_DIR)
RM = rm -f
ARNAME = ar rcs $(NAME)
all: $(NAME)
$(NAME): $(OBJS)
	$(ARNAME)	$(OBJS)
%.o: %.c libft.h
	$(CC)	$(DIR_FLAG)	$(FLAGS) -c $< -o $@
clean:
	$(RM)	$(OBJS)	
fclean: clean
	$(RM)	$(NAME)
re: fclean	all
.PHONY: all clean fclean re 
