/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:37:05 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:37:19 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_all_temp_files(void)
{
	char	*temp_pattern;
	int		i;
	char	*temp_file;
	char	*suffix;

	i = 0;
	while (i < 1000)
	{
		suffix = ft_itoa(i);
		temp_pattern = ft_strjoin("heredoc_", suffix);
		temp_file = ft_strjoin("/tmp/minishell_", temp_pattern);
		unlink(temp_file);
		free(suffix);
		free(temp_pattern);
		free(temp_file);
		i++;
	}
}

void	cleanup_heredoc_files(t_cmd *commands)
{
	t_cmd	*current;
	t_redir	*redir;

	current = commands;
	while (current)
	{
		redir = current->in;
		while (redir)
		{
			if (redir->type == OP_HEREDOC && redir->heredoc_fd >= 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			if (redir->temp_file)
			{
				unlink(redir->temp_file);
				free(redir->temp_file);
				redir->temp_file = NULL;
			}
			redir = redir->next;
		}
		current = current->next;
	}
}
