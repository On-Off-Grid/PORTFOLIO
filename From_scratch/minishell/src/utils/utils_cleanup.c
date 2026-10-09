/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:40:31 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:40:32 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		if (redir->heredoc_fd >= 0)
			close(redir->heredoc_fd);
		if (redir->temp_file)
		{
			unlink(redir->temp_file);
			free(redir->temp_file);
		}
		free(redir);
		redir = tmp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_argv(cmds->argv);
		free_redir_list(cmds->in);
		free_redir_list(cmds->out);
		free(cmds);
		cmds = tmp;
	}
}
