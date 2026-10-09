/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:37:02 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:37:03 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_heredoc_file(char *delimiter)
{
	char	*tmp_file;
	int		fd;

	tmp_file = generate_temp_filename(delimiter);
	if (!tmp_file)
		return (NULL);
	fd = open(tmp_file, O_WRONLY);
	if (fd < 0)
	{
		free(tmp_file);
		return (NULL);
	}
	write_heredoc_content(fd, delimiter);
	close(fd);
	if (g_signal == SIGINT)
	{
		unlink(tmp_file);
		free(tmp_file);
		return (NULL);
	}
	return (tmp_file);
}

static void	write_heredoc_line(int fd, char *line, char *delimiter)
{
	char	*expanded_line;

	expanded_line = evaluate_heredoc_line(line, delimiter);
	write(fd, expanded_line, ft_strlen(expanded_line));
	write(fd, "\n", 1);
	free(expanded_line);
}

static int	read_heredoc_loop(int fd, char *delimiter)
{
	char	*line;
	char	*clean_delimiter;

	clean_delimiter = remove_quotes(delimiter);
	line = "";
	while (line)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, clean_delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write_heredoc_line(fd, line, delimiter);
		free(line);
	}
	free(clean_delimiter);
	return (0);
}

static int	handle_heredoc_child(char *tmp_file, char *delimiter)
{
	int	fd;

	signal(SIGINT, SIG_DFL);
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		exit(1);
	read_heredoc_loop(fd, delimiter);
	close(fd);
	exit(0);
	return (0);
}

int	handle_heredoc_input(t_redir *redir)
{
	char	*tmp_file;
	pid_t	pid;
	int		status;
	int		result;

	tmp_file = generate_temp_filename(redir->file);
	if (!tmp_file)
		return (-1);
	g_signal = 0;
	pid = fork();
	if (pid == -1)
	{
		free(tmp_file);
		return (-1);
	}
	if (pid == 0)
		handle_heredoc_child(tmp_file, redir->file);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	restore_main_signals();
	result = handle_heredoc_signals(tmp_file, status);
	if (result != 0)
		return (result);
	return (open_heredoc_file(tmp_file));
}
