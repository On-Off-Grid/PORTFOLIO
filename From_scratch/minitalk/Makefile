# Names of the executables
SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Source files for each program
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Object files derived from source files
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Rule for using the libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I. -I$(LIBFT_DIR)

# Main target builds both executables
all: $(LIBFT) $(SERVER) $(CLIENT)

# Build the libft library
$(LIBFT):
	make -C $(LIBFT_DIR)

# Link the server executable
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER) $(LIBFT)

# Link the client executable
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT) $(LIBFT)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	make -C $(LIBFT_DIR) clean

# Clean object files and executables
fclean: clean
	rm -f $(SERVER) $(CLIENT)
	make -C $(LIBFT_DIR) fclean

# Full rebuild
re: fclean all

# These targets don't correspond to files
.PHONY: all clean fclean re
