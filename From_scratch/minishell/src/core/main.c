/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:30:54 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:30:56 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	execute_commands(t_cmd *commands, t_shell_ctx *ctx)
{
	int	status;

	status = exec_cmds(commands, &ctx->current_env);
	update_shell_status(ctx, status);
	cleanup_heredoc_files(commands);
	free_cmds(commands);
}

static int	validate_and_expand(char *line, t_token **tokens, t_shell_ctx *ctx)
{
	*tokens = lexer(line);
	if (!*tokens)
		return (0);
	if (!validate_tokens_syntax(*tokens))
	{
		update_shell_status(ctx, 2);
		free_tokens(*tokens);
		return (0);
	}
	expand_token_vars(*tokens, ctx);
	return (1);
}

void	process_line(char *line, t_shell_ctx *ctx)
{
	t_token	*tokens;
	t_cmd	*commands;

	if (!line || !*line)
		return ;
	if (!validate_and_expand(line, &tokens, ctx))
		return ;
	commands = parse_tokens(tokens);
	if (commands)
	{
		if (process_all_heredocs(commands, ctx) < 0)
		{
			cleanup_heredoc_files(commands);
			free_cmds(commands);
			free_tokens(tokens);
			return ;
		}
		execute_commands(commands, ctx);
	}
	free_tokens(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_ctx	ctx;

	init_shell_context(&ctx, envp);
	init_signals();
	main_loop(&ctx, argc, argv);
	cleanup_all_temp_files();
	return (ctx.last_status);
}
