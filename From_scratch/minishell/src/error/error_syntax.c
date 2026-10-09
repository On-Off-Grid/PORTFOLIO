/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:21:20 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:21:24 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Validates tokens for syntax errors, particularly handling redirection and pipe
 * operators that don't have appropriate arguments.
 * Returns 1 if syntax is valid, 0 if there's an error
 */
int	validate_tokens_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!check_initial_pipe(tokens))
		return (0);
	current = tokens;
	while (current)
	{
		next = current->next;
		if (is_redirection_operator(current->type))
		{
			if (!validate_redirection(next))
				return (0);
		}
		else if (current->type == PIPE)
		{
			if (!validate_pipe(next))
				return (0);
		}
		current = next;
	}
	return (1);
}
