/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:34:33 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:34:34 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_child_process(t_cmd *cmd, char *cmd_path, char **envp)
{
	if (handle_redirections(cmd) != 0)
		exit(1);
	if (execve(cmd_path, cmd->argv, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
	return (0);
}

static int	handle_wait_interrupt(pid_t pid)
{
	int	status;

	if (errno == EINTR && g_signal == SIGINT)
	{
		kill(pid, SIGINT);
		waitpid(pid, &status, 0);
		g_signal = 0;
		return (130);
	}
	if (errno != EINTR)
	{
		perror("waitpid");
		return (1);
	}
	return (0);
}

static int	get_process_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	handle_parent_process(pid_t pid, char *cmd_path)
{
	int	status;
	int	wait_result;
	int	interrupt_result;

	if (cmd_path)
		free(cmd_path);
	while (1)
	{
		wait_result = waitpid(pid, &status, 0);
		if (wait_result != -1)
			break ;
		interrupt_result = handle_wait_interrupt(pid);
		if (interrupt_result != 0)
			return (interrupt_result);
	}
	return (get_process_exit_status(status));
}

int	exec_external_cmd(t_cmd *cmd, char **envp)
{
	char	*cmd_path;
	pid_t	pid;
	int		error_code;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	cmd_path = find_command_path(cmd->argv[0], envp);
	error_code = handle_cmd_not_found(cmd, cmd_path);
	if (error_code != 0)
		return (error_code);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (cmd_path)
			free(cmd_path);
		return (1);
	}
	if (pid == 0)
		return (handle_child_process(cmd, cmd_path, envp));
	else
		return (handle_parent_process(pid, cmd_path));
}
