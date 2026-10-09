/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:35:02 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:35:03 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	has_non_empty_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		if (cmd->argv[i] && ft_strlen(cmd->argv[i]) > 0)
			return (1);
		i++;
	}
	return (0);
}

static void	compact_args(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->argv[i])
	{
		if (cmd->argv[i] && ft_strlen(cmd->argv[i]) > 0)
		{
			if (i != j)
			{
				cmd->argv[j] = cmd->argv[i];
				cmd->argv[i] = NULL;
			}
			j++;
		}
		else if (cmd->argv[i])
		{
			free(cmd->argv[i]);
			cmd->argv[i] = NULL;
		}
		i++;
	}
	cmd->argv[j] = NULL;
}

int	handle_empty_command(t_cmd *cmd)
{
	if (!has_non_empty_args(cmd))
		return (0);
	compact_args(cmd);
	if (!cmd->argv[0])
		return (0);
	return (-1);
}

int	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
		return (-1);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		close(*saved_stdin);
		return (-1);
	}
	return (0);
}

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
