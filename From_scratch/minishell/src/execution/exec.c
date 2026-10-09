/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:24:01 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:24:06 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	return (apply_redirections(cmd->in, cmd->out));
}

static int	exec_builtin_cmd(t_cmd *cmd, char ***envp)
{
	int	redir_result;
	int	saved_stdin;
	int	saved_stdout;
	int	builtin_result;

	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
		return (1);
	redir_result = handle_redirections(cmd);
	if (redir_result != 0)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (redir_result);
	}
	builtin_result = exec_builtin(cmd, envp);
	restore_std_fds(saved_stdin, saved_stdout);
	return (builtin_result);
}

int	exec_single_cmd(t_cmd *cmd, char ***envp)
{
	int	empty_result;
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		if (cmd && (cmd->in || cmd->out))
		{
			if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
				return (1);
			result = handle_redirections(cmd);
			restore_std_fds(saved_stdin, saved_stdout);
			return (result);
		}
		return (0);
	}
	empty_result = handle_empty_command(cmd);
	if (empty_result != -1)
		return (empty_result);
	if (is_builtin(cmd->argv[0]))
		return (exec_builtin_cmd(cmd, envp));
	else
		return (exec_external_cmd(cmd, *envp));
}

int	count_cmds(t_cmd *cmds)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmds;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
