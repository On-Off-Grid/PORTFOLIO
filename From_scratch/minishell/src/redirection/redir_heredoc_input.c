/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:38:04 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:39:26 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_line_from_stdin(void)
{
	char	buffer[1024];
	char	*line;
	int		bytes_read;
	int		i;

	bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	i = 0;
	while (i < bytes_read && buffer[i] != '\n')
		i++;
	if (i < bytes_read)
		buffer[i] = '\0';
	line = ft_strdup(buffer);
	return (line);
}

char	*get_input_line(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("> "));
	else
		return (read_line_from_stdin());
}

int	handle_signal_interrupt(char *line, t_shell_ctx *ctx)
{
	if (g_signal == SIGINT)
	{
		ctx->last_status = 130;
		if (line)
			free(line);
		return (-1);
	}
	return (0);
}

void	print_eof_warning(char *delimiter, t_shell_ctx *ctx)
{
	int		line_number;
	char	*line_num;

	if (isatty(STDIN_FILENO))
		line_number = 1;
	else
		line_number = ctx->last_status + 1;
	line_num = ft_itoa(line_number);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(line_num, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	free(line_num);
}

void	process_and_write_line(int fd, char *line, char *delimiter)
{
	char	*processed_line;

	processed_line = evaluate_heredoc_line(line, delimiter);
	write(fd, processed_line, ft_strlen(processed_line));
	write(fd, "\n", 1);
	free(processed_line);
}
