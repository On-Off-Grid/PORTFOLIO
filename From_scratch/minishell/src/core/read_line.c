/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:31:03 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:31:04 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	find_unclosed_quote(const char *s)
{
	int	in_s;
	int	in_d;

	in_s = 0;
	in_d = 0;
	while (s && *s)
	{
		if (*s == '\'' && !in_d)
			in_s = !in_s;
		else if (*s == '"' && !in_s)
			in_d = !in_d;
		s++;
	}
	if (in_s)
		return ('\'');
	if (in_d)
		return ('"');
	return (0);
}

static void	write_error_message(char uq)
{
	char	message[64];

	if (uq == '"')
		ft_strcpy(message, "minishell: unexpected EOF while looking for "
			"matching `\"'\n");
	else
		ft_strcpy(message, "minishell: unexpected EOF while looking for "
			"matching `''\n");
	write(STDERR_FILENO, message, ft_strlen(message));
}

void	read_line(int argc, char **argv, char **line,
	volatile sig_atomic_t *g_last_status)
{
	char	uq;

	(void)argc;
	(void)argv;
	if (line && *line)
	{
		uq = find_unclosed_quote(*line);
		if (uq)
		{
			write_error_message(uq);
			*g_last_status = 2;
			free(*line);
			*line = NULL;
		}
	}
}
