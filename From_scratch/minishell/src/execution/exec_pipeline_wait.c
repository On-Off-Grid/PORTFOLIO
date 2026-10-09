/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_wait.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:34:53 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:34:54 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

static void	kill_remaining_processes(pid_t *pids, int start, int n)
{
	int	status;

	while (start < n)
	{
		kill(pids[start], SIGINT);
		waitpid(pids[start], &status, 0);
		start++;
	}
}

int	wait_pipeline_children(pid_t *pids, int n)
{
	int	i;
	int	status;
	int	last_exit;
	int	wait_result;

	last_exit = 0;
	i = 0;
	while (i < n)
	{
		wait_result = waitpid(pids[i], &status, 0);
		if (wait_result == -1 && errno == EINTR && g_signal == SIGINT)
		{
			g_signal = 0;
			kill_remaining_processes(pids, i, n);
			return (130);
		}
		if (i == n - 1)
			last_exit = get_exit_status(status);
		i++;
	}
	return (last_exit);
}
