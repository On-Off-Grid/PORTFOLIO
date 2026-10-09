/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:40:05 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:40:06 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	g_signal = SIGQUIT;
}

void	handle_sigint_child(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit_child(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}
