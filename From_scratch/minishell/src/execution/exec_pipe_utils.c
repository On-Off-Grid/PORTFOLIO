/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:34:42 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:34:43 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	create_child_process(t_pipe_ctx *ctx, t_cmd *cur)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		setup_child_pipes(ctx);
		close_child_pipes(ctx);
		exec_pipeline_child(cur, ctx->envp);
	}
	return (pid);
}

static void	close_parent_pipes(t_pipe_ctx *ctx)
{
	if (ctx->i > 0)
		close(ctx->pipefd[ctx->i - 1][0]);
	if (ctx->i < ctx->n - 1)
		close(ctx->pipefd[ctx->i][1]);
}

static int	setup_pipes(t_pipe_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->n - 1)
	{
		if (pipe(ctx->pipefd[i]) == -1)
		{
			perror("pipe");
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	fork_pipeline_processes(t_cmd *cmds, t_pipe_ctx *ctx, pid_t *pids)
{
	t_cmd	*cur;

	cur = cmds;
	ctx->i = 0;
	while (cur && ctx->i < ctx->n)
	{
		pids[ctx->i] = create_child_process(ctx, cur);
		if (pids[ctx->i] == -1)
			return (-1);
		close_parent_pipes(ctx);
		cur = cur->next;
		ctx->i++;
	}
	return (0);
}

int	exec_pipeline_cmds(t_cmd *cmds, char ***envp)
{
	t_pipe_ctx	ctx;
	pid_t		*pids;
	int			result;

	ctx.n = count_cmds(cmds);
	ctx.envp = envp;
	pids = malloc(sizeof(pid_t) * ctx.n);
	if (!pids)
		return (1);
	if (setup_pipes(&ctx) == -1)
	{
		free(pids);
		return (1);
	}
	if (fork_pipeline_processes(cmds, &ctx, pids) == -1)
	{
		free(pids);
		return (1);
	}
	result = wait_pipeline_children(pids, ctx.n);
	free(pids);
	return (result);
}
