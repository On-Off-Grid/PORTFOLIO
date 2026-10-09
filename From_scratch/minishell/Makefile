# ==========================================
# Minishell - Simplified Modular Makefile
# ==========================================

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
LIBFT_DIR = libft

# Source files (modular organization by functionality)
CORE_SRCS = core/main.c core/main_lifecycle.c core/read_line.c
LEXER_SRCS = lexer/lexer.c lexer/lexer_utils.c lexer/lexer_operators.c lexer/lexer_tokens.c
PARSER_SRCS = parser/parser.c parser/parser_utils.c parser/parser_redir.c
EXECUTION_SRCS = execution/exec.c execution/exec_utils.c execution/exec_core.c execution/exec_path.c execution/exec_external.c execution/exec_pipeline.c execution/exec_pipe_utils.c execution/exec_pipeline_wait.c
REDIRECTION_SRCS = redirection/redir.c redirection/redir_heredoc.c redirection/redir_heredoc_utils.c redirection/redir_heredoc_utils2.c redirection/redir_heredoc_read.c redirection/redir_heredoc_expansion.c redirection/redir_heredoc_parse.c redirection/redir_heredoc_input.c redirection/redir_heredoc_file_ops.c redirection/redir_heredoc_signals.c redirection/redir_heredoc_cleanup.c redirection/redir_io.c
BUILTIN_SRCS = builtin/builtin_basic.c builtin/builtin_env.c builtin/builtin_env_export.c builtin/builtin_env_utils.c builtin/builtin_exit.c builtin/builtin_env_simple.c
ENVIRONMENT_SRCS = environment/env_utils.c environment/env_utils_basic.c environment/env_utils_modify.c
SIGNAL_SRCS = signals/signals.c signals/signal_handlers.c
ERROR_SRCS = error/error_handling.c error/error_print.c error/error_file.c error/error_exec.c error/error_validate.c error/error_cleanup.c error/error_syntax.c error/error_syntax_utils.c
UTILITY_SRCS = utils/utils.c utils/utils_cleanup.c utils/utils_expansion.c utils/utils_context.c

# All source files
SRCS = $(CORE_SRCS) $(LEXER_SRCS) $(PARSER_SRCS) $(EXECUTION_SRCS) \
       $(REDIRECTION_SRCS) $(BUILTIN_SRCS) $(ENVIRONMENT_SRCS) \
       $(SIGNAL_SRCS) $(ERROR_SRCS) $(UTILITY_SRCS)

# Object files
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Include paths
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

# Library
LIBFT = $(LIBFT_DIR)/libft.a

# Colors for output
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m # No Color

# Build rules
.PHONY: all clean fclean re libft norm info help

all: $(NAME)
	@echo "$(GREEN)✅ Minishell built successfully!$(NC)"

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(NC)"
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔨 Compiling $<$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Library
$(LIBFT):
	@echo "$(BLUE)📚 Building libft...$(NC)"
	@make -C $(LIBFT_DIR)

libft:
	@make -C $(LIBFT_DIR)

# Cleaning
clean:
	@echo "$(RED)🧹 Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)🧹 Full clean...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all
