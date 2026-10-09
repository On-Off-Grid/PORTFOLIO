/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:36:38 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:36:40 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_redir(t_redir **head, int type, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = safe_malloc(sizeof(t_redir));
	new_redir->type = type;
	new_redir->file = file;
	new_redir->heredoc_fd = -1;
	new_redir->temp_file = NULL;
	new_redir->next = NULL;
	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

int	is_redirection_token(t_token_type type)
{
	return (type == OP_IN || type == OP_OUT || type == OP_APPEND
		|| type == OP_HEREDOC);
}

int	get_redir_type(t_token_type type)
{
	if (type == OP_IN)
		return (OP_IN);
	if (type == OP_OUT)
		return (OP_OUT);
	if (type == OP_APPEND)
		return (OP_APPEND);
	if (type == OP_HEREDOC)
		return (OP_HEREDOC);
	return (-1);
}

t_token	*handle_redirection_token(t_token *current, t_cmd *cmd)
{
	int		redir_type;
	char	*filename;

	redir_type = get_redir_type(current->type);
	current = current->next;
	if (!current || !current->value)
		return (NULL);
	filename = merge_adjacent_tokens(&current);
	if (redir_type == OP_IN || redir_type == OP_HEREDOC)
		add_redir(&cmd->in, redir_type, filename);
	else
		add_redir(&cmd->out, redir_type, filename);
	return (current);
}

t_token	*handle_word_token(t_token *current, t_cmd *cmd)
{
	char	*arg;

	arg = merge_adjacent_tokens(&current);
	add_arg(cmd, arg);
	return (current);
}
