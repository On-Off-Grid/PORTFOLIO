/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:36:34 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:36:36 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*parse_redirections(t_token *tokens, t_cmd *cmd)
{
	t_token	*current;

	current = tokens;
	while (current && current->type != PIPE)
	{
		if (is_redirection_token(current->type))
		{
			current = handle_redirection_token(current, cmd);
			if (!current)
				return (NULL);
		}
		else if (current->type == WORD || current->type == SQUOTE
			|| current->type == DQUOTE)
		{
			current = handle_word_token(current, cmd);
		}
		else
			current = current->next;
	}
	return (current);
}

static t_token	*handle_pipe_token(t_token *token, t_cmd **current_cmd)
{
	t_cmd	*new_command;

	new_command = new_cmd();
	(*current_cmd)->next = new_command;
	*current_cmd = new_command;
	return (token->next);
}

static int	is_empty_command(t_cmd *cmd)
{
	if (cmd->in || cmd->out)
		return (0);
	return (!cmd->argv || !cmd->argv[0]);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current_cmd;
	t_token	*current_token;

	if (!tokens)
		return (NULL);
	head = new_cmd();
	current_cmd = head;
	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == PIPE)
		{
			if (is_empty_command(current_cmd))
				return (NULL);
			current_token = handle_pipe_token(current_token, &current_cmd);
		}
		else
			current_token = parse_redirections(current_token, current_cmd);
	}
	if (is_empty_command(current_cmd))
		return (NULL);
	return (head);
}
