/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:38:21 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:38:22 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Static function to check delimiter match has been inlined */

static int	handle_heredoc_line_error(char *line, char *clean_delimiter)
{
	if (line)
		free(line);
	free(clean_delimiter);
	if (g_signal == SIGINT)
		return (130);
	else
		return (0);
}

static void	write_expanded_line(int fd, char *line, char *delimiter)
{
	char	*expanded_line;

	expanded_line = evaluate_heredoc_line(line, delimiter);
	write(fd, expanded_line, ft_strlen(expanded_line));
	write(fd, "\n", 1);
	free(expanded_line);
}

int	read_heredoc_lines(int fd, char *delimiter)
{
	char	*line;
	char	*clean_delimiter;

	write(2, "DEBUG: read_heredoc_lines called\n", 33);
	g_signal = 0;
	clean_delimiter = remove_quotes(delimiter);
	while (1)
	{
		if (g_signal == SIGINT)
			return (free(clean_delimiter), 130);
		line = readline("> ");
		if (g_signal == SIGINT || !line)
			return (handle_heredoc_line_error(line, clean_delimiter));
		if (ft_strcmp(line, clean_delimiter) == 0)
			return (free(line), free(clean_delimiter), 0);
		write_expanded_line(fd, line, delimiter);
		free(line);
	}
}

void	write_heredoc_content(int fd, char *delimiter)
{
	g_signal = 0;
	read_heredoc_lines(fd, delimiter);
}
