/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:34:46 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:34:48 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_child_pipes(t_pipe_ctx *ctx)
{
	if (ctx->i > 0)
		dup2(ctx->pipefd[ctx->i - 1][0], STDIN_FILENO);
	if (ctx->i < ctx->n - 1)
		dup2(ctx->pipefd[ctx->i][1], STDOUT_FILENO);
}

void	close_child_pipes(t_pipe_ctx *ctx)
{
	int	j;

	j = 0;
	while (j < ctx->n - 1)
	{
		close(ctx->pipefd[j][0]);
		close(ctx->pipefd[j][1]);
		j++;
	}
}

static void	exec_builtin_child(t_cmd *cur, char ***envp)
{
	if (ft_strcmp(cur->argv[0], "echo") == 0)
		exit(builtin_echo(cur->argv));
	if (ft_strcmp(cur->argv[0], "cd") == 0)
		exit(builtin_cd(cur->argv, *envp));
	if (ft_strcmp(cur->argv[0], "pwd") == 0)
		exit(builtin_pwd());
	if (ft_strcmp(cur->argv[0], "export") == 0)
		exit(exec_export_builtin(cur->argv, envp));
	if (ft_strcmp(cur->argv[0], "unset") == 0)
		exit(exec_unset_builtin(cur->argv, envp));
	if (ft_strcmp(cur->argv[0], "env") == 0)
		exit(builtin_env(*envp));
	if (ft_strcmp(cur->argv[0], "exit") == 0)
		exit(builtin_exit(cur->argv));
}

static void	exec_external_child(t_cmd *cur, char ***envp)
{
	char	*cmd_path;

	cmd_path = find_command_path(cur->argv[0], *envp);
	if (cmd_path)
	{
		execve(cmd_path, cur->argv, *envp);
		free(cmd_path);
		print_command_not_found(cur->argv[0]);
	}
	else
	{
		print_command_not_found(cur->argv[0]);
	}
	exit(127);
}

void	exec_pipeline_child(t_cmd *cur, char ***envp)
{
	if (handle_redirections(cur) != 0)
		exit(1);
	if (is_builtin(cur->argv[0]))
		exec_builtin_child(cur, envp);
	else
		exec_external_child(cur, envp);
}
