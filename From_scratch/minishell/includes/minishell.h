/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:49:02 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:49:04 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	WORD,
	SQUOTE,
	DQUOTE,
	OP_IN,
	OP_OUT,
	OP_HEREDOC,
	OP_APPEND,
	PIPE,
	VAR,
	DOLLAR
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	int					has_leading_space;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	int					type;
	char				*file;
	int					heredoc_fd;
	char				*temp_file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char				**argv;
	t_redir				*in;
	t_redir				*out;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_pipe_ctx
{
	int					n;
	int					i;
	int					pipefd[64][2];
	char				***envp;
}	t_pipe_ctx;

typedef struct s_shell_ctx
{
	int					last_status;
	char				**original_env;
	char				**current_env;
}	t_shell_ctx;

# define NODE_CMD 0
# define NODE_PIPE 1
# define NODE_SEQ 2

t_token				*lexer(const char *line);

// Lexer utility functions
t_token_type		get_operator_type(const char *str, int *len);
t_token				*init_token_list(void);
void				add_token(t_token **head, t_token_type type, char *value,
						int has_space);
int					skip_whitespace(const char *line, int *i);

void				process_operator(const char *line, int *i, t_token **tokens,
						int has_space);
void				handle_quotes(const char *line, int *i, t_token **tokens,
						int has_space);
void				handle_word(const char *line, int *i, t_token **tokens,
						int has_space);

t_cmd				*parse_tokens(t_token *tokens);
int					get_redir_type(t_token_type type);
void				read_line(int argc, char **argv, char **line,
						volatile sig_atomic_t *g_last_status);

// Parser utility functions
t_cmd				*new_cmd(void);
char				*merge_first_token(char *merged, t_token **token);
char				*merge_remaining_tokens(char *merged, t_token **token);
char				*merge_adjacent_tokens(t_token **current);
void				add_arg(t_cmd *cmd, char *arg);

// Parser redirection functions
void				add_redir(t_redir **head, int type, char *file);
int					is_redirection_token(t_token_type type);
t_token				*handle_redirection_token(t_token *current, t_cmd *cmd);
t_token				*handle_word_token(t_token *current, t_cmd *cmd);

//t_node			*build_ast(t_cmd *cmds);
int					exec_cmds(t_cmd *cmds, char ***envp);
char				*find_command_path(char *cmd, char **envp);
int					apply_redirections(t_redir *in, t_redir *out);

/* redir_heredoc.c */
char				*create_heredoc_file(char *delimiter);
int					handle_heredoc_input(t_redir *redir);
char				*generate_temp_filename(char *delimiter);
void				setup_heredoc_signals(void);
void				restore_main_signals(void);
char				*generate_random_suffix(void);
int					read_heredoc_lines(int fd, char *delimiter);
void				write_heredoc_content(int fd, char *delimiter);
int					has_quotes(char *delimiter);
char				*remove_quotes(char *delimiter);
char				*evaluate_heredoc_line(char *line, char *delimiter);

/* redir_heredoc_utils2.c */
int					open_heredoc_file(char *tmp_file);
int					handle_heredoc_signals(char *tmp_file, int status);

/* redir_heredoc_input.c */
char				*read_line_from_stdin(void);
char				*get_input_line(void);
int					handle_signal_interrupt(char *line, t_shell_ctx *ctx);
void				print_eof_warning(char *delimiter, t_shell_ctx *ctx);
void				process_and_write_line(int fd, char *line, char *delimiter);

/* redir_heredoc_file_ops.c */
int					open_temp_file(char *temp_file);
int					finalize_heredoc_file(char *temp_file, int result);

/* redir_heredoc_parse.c - Parse-time heredoc processing */
int					process_all_heredocs(t_cmd *commands, t_shell_ctx *ctx);
int					process_cmd_heredocs(t_cmd *cmd, t_shell_ctx *ctx,
						int *count);
int					create_heredoc_during_parse(char *delimiter,
						t_redir *redir, t_shell_ctx *ctx);
void				cleanup_heredoc_files(t_cmd *commands);
void				cleanup_all_temp_files(void);
void				setup_parse_heredoc_signals(void);
void				heredoc_parse_sigint(int sig);
int					read_heredoc_input(int fd, char *delimiter,
						t_shell_ctx *ctx);

/* redir_io.c */
int					handle_regular_input(t_redir *redir);
int					handle_input_redir(t_redir *redir);
int					handle_output_redir(t_redir *redir);

int					is_builtin(char *cmd);
int					handle_redirections(t_cmd *cmd);
int					handle_cmd_not_found(t_cmd *cmd, char *cmd_path);
int					exec_single_cmd(t_cmd *cmd, char ***envp);
int					exec_builtin(t_cmd *cmd, char ***envp);
int					exec_export_builtin(char **argv, char ***envp);
int					exec_unset_builtin(char **argv, char ***envp);
int					count_cmds(t_cmd *cmds);
int					exec_external_cmd(t_cmd *cmd, char **envp);
int					exec_pipeline_cmds(t_cmd *cmds, char ***envp);
void				setup_child_pipes(t_pipe_ctx *ctx);
void				close_child_pipes(t_pipe_ctx *ctx);
void				exec_pipeline_child(t_cmd *cur, char ***envp);
int					wait_pipeline_children(pid_t *pids, int n);

int					builtin_echo(char **argv);
int					builtin_cd(char **argv, char **envp);
int					builtin_pwd(void);
int					builtin_export(char **argv, t_shell_ctx *ctx);
int					builtin_unset(char **argv, t_shell_ctx *ctx);
int					builtin_env(char **envp);
int					builtin_exit(char **argv);
void				export_error(char *arg);
int					check_identifier_validity(char *arg, char **split);
char				**add_export_var(char **argv, int i, char ***envp);
void				init_signals(void);
void				handle_sigint(int sig);
void				handle_heredoc_sigint(int sig);
void				handle_sigquit(int sig);
void				handle_sigint_child(int sig);
void				handle_sigquit_child(int sig);
void				init_child_signals(void);
void				restore_signals(void);

void				perror_exit(const char *msg);
void				*safe_malloc(size_t size);

/* Enhanced error handling functions */
void				print_error(const char *cmd, const char *arg,
						const char *msg);
void				print_command_not_found(const char *cmd);
void				print_syntax_error(const char *token);
void				print_file_error(const char *filename,
						const char *error_type);
void				print_permission_denied(const char *filename);
void				print_no_such_file(const char *filename);
void				print_is_directory(const char *filename);
int					handle_fork_error(void);
int					handle_pipe_error(void);
int					handle_execve_error(const char *cmd);
int					validate_builtin_args(const char *cmd, char **argv,
						int min_args, int max_args);
int					validate_file_access(const char *filename, int mode);
int					handle_redirection_error(const char *filename,
						int redir_type);
int					check_output_file(const char *filename);
void				cleanup_on_error(t_token *tokens, t_cmd *commands);
int					is_valid_identifier(const char *str);
void				print_invalid_identifier(const char *cmd,
						const char *identifier);
int					check_memory_allocation(void *ptr,
						const char *function_name);
int					validate_tokens_syntax(t_token *tokens);

void				free_tokens(t_token *tokens);
void				free_cmds(t_cmd *cmds);
char				*get_env_value(char **envp, const char *key);
void				free_split(char **split);
char				**env_add_var(char **envp, const char *key,
						const char *value);
char				**env_update_var(char **envp, const char *key,
						const char *value);
char				**env_remove_var(char **envp, const char *key);
int					env_var_exists(char **envp, const char *key);
char				*expand_vars(char *str, char **envp, int last_status);
void				expand_token_vars(t_token *tokens, t_shell_ctx *ctx);
void				init_shell_context(t_shell_ctx *ctx, char **envp);
void				update_shell_status(t_shell_ctx *ctx, int status);
void				update_shell_env(t_shell_ctx *ctx, char **new_env);
int					should_free_env(t_shell_ctx *ctx);

// Utils expansion helper functions
char				*expand_single_var(char *str, int *i, char **envp,
						int last_status);
char				*append_expansion(char *result, char *expansion);
char				*append_char(char *result, char c);

// Environment utility helper functions
char				**allocate_new_env(char **envp, int *count);
char				*create_env_var_string(const char *key, const char *value);

// Exec utils functions
int					handle_empty_command(t_cmd *cmd);
int					save_std_fds(int *saved_stdin, int *saved_stdout);
void				restore_std_fds(int saved_stdin, int saved_stdout);

/* main_lifecycle.c */
void				handle_signal_event(t_shell_ctx *ctx);
void				main_loop(t_shell_ctx *ctx, int argc, char **argv);
void				process_line(char *line, t_shell_ctx *ctx);

/* error_syntax_utils.c */
int					is_redirection_operator(t_token_type type);
int					is_valid_redirection_target(t_token_type type);
int					validate_redirection(t_token *next);
int					validate_pipe(t_token *next);
int					check_initial_pipe(t_token *tokens);

#endif
