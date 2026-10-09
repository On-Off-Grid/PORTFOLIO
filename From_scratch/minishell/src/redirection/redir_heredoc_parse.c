/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:38:11 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:39:47 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_heredoc_input(int fd, char *delimiter, t_shell_ctx *ctx)
{
	char	*line;

	while (1)
	{
		line = get_input_line();
		if (isatty(STDIN_FILENO) && handle_signal_interrupt(line, ctx) == -1)
			return (-1);
		if (!line)
		{
			print_eof_warning(delimiter, ctx);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_and_write_line(fd, line, delimiter);
		free(line);
	}
	return (0);
}

int	create_heredoc_during_parse(char *delimiter, t_redir *redir,
	t_shell_ctx *ctx)
{
	char	*temp_file;
	int		fd;
	int		result;

	temp_file = generate_temp_filename(delimiter);
	if (!temp_file)
		return (-1);
	redir->temp_file = ft_strdup(temp_file);
	fd = open_temp_file(temp_file);
	if (fd < 0)
		return (-1);
	setup_parse_heredoc_signals();
	result = read_heredoc_input(fd, delimiter, ctx);
	close(fd);
	return (finalize_heredoc_file(temp_file, result));
}

int	process_cmd_heredocs(t_cmd *cmd, t_shell_ctx *ctx, int *count)
{
	t_redir	*redir;

	redir = cmd->in;
	while (redir)
	{
		if (redir->type == OP_HEREDOC)
		{
			if (++(*count) > 16)
			{
				ft_putstr_fd("minishell: maximum here-document count exceeded\n",
					STDERR_FILENO);
				return (-1);
			}
			redir->heredoc_fd = create_heredoc_during_parse(redir->file,
					redir, ctx);
			if (redir->heredoc_fd < 0)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

int	process_all_heredocs(t_cmd *commands, t_shell_ctx *ctx)
{
	t_cmd	*current;
	int		heredoc_count;

	current = commands;
	heredoc_count = 0;
	g_signal = 0;
	while (current && heredoc_count < 16)
	{
		if (process_cmd_heredocs(current, ctx, &heredoc_count) < 0)
		{
			cleanup_heredoc_files(commands);
			init_signals();
			return (-1);
		}
		current = current->next;
	}
	init_signals();
	return (0);
}
