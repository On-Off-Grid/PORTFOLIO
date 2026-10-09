/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:34:29 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:34:30 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_export_builtin(char **argv, char ***envp)
{
	t_shell_ctx	temp_ctx;
	int			result;

	init_shell_context(&temp_ctx, *envp);
	temp_ctx.current_env = *envp;
	result = builtin_export(argv, &temp_ctx);
	*envp = temp_ctx.current_env;
	return (result);
}

int	exec_unset_builtin(char **argv, char ***envp)
{
	t_shell_ctx	temp_ctx;
	int			result;

	init_shell_context(&temp_ctx, *envp);
	temp_ctx.current_env = *envp;
	result = builtin_unset(argv, &temp_ctx);
	*envp = temp_ctx.current_env;
	return (result);
}

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv, *envp));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (exec_export_builtin(cmd->argv, envp));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (exec_unset_builtin(cmd->argv, envp));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(*envp));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd->argv));
	return (1);
}

int	exec_cmds(t_cmd *cmds, char ***envp)
{
	int	count;

	if (!cmds)
		return (0);
	count = count_cmds(cmds);
	if (count == 1)
		return (exec_single_cmd(cmds, envp));
	else
		return (exec_pipeline_cmds(cmds, envp));
}
