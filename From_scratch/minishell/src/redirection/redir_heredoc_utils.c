/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:38:36 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:38:37 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*generate_random_suffix(void)
{
	static int	counter = 0;
	char		*suffix;

	suffix = ft_itoa(counter);
	counter++;
	return (suffix);
}

char	*generate_temp_filename(char *delimiter)
{
	char	*tmp_file;
	char	*random_suffix;
	char	*temp_str;
	int		fd;
	int		attempts;

	(void)delimiter;
	attempts = 0;
	while (attempts < 100)
	{
		random_suffix = generate_random_suffix();
		temp_str = ft_strjoin("heredoc_", random_suffix);
		tmp_file = ft_strjoin("/tmp/minishell_", temp_str);
		free(temp_str);
		free(random_suffix);
		fd = open(tmp_file, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd >= 0)
		{
			close(fd);
			return (tmp_file);
		}
		free(tmp_file);
		attempts++;
	}
	return (NULL);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_main_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
