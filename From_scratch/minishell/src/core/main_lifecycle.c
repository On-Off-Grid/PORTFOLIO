/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:30:59 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:31:00 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal_event(t_shell_ctx *ctx)
{
	if (g_signal == SIGINT)
	{
		update_shell_status(ctx, 130);
		g_signal = 0;
	}
	else if (g_signal == SIGQUIT)
	{
		update_shell_status(ctx, 131);
		g_signal = 0;
	}
}

void	main_loop(t_shell_ctx *ctx, int argc, char **argv)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		read_line(argc, argv, &line, &ctx->last_status);
		if (!line)
			continue ;
		handle_signal_event(ctx);
		if (*line)
			add_history(line);
		process_line(line, ctx);
		free(line);
	}
}
