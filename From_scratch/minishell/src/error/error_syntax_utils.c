/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:21:47 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:21:51 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirection_operator(t_token_type type)
{
	return (type == OP_IN || type == OP_OUT || type == OP_HEREDOC
		|| type == OP_APPEND);
}

int	is_valid_redirection_target(t_token_type type)
{
	return (type == WORD || type == SQUOTE || type == DQUOTE);
}

int	validate_redirection(t_token *next)
{
	if (!next || !is_valid_redirection_target(next->type))
	{
		print_syntax_error("newline");
		return (0);
	}
	return (1);
}

int	validate_pipe(t_token *next)
{
	if (!next)
	{
		print_syntax_error("newline");
		return (0);
	}
	else if (next->type == PIPE)
	{
		print_syntax_error("|");
		return (0);
	}
	return (1);
}

int	check_initial_pipe(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == PIPE)
	{
		print_syntax_error("|");
		return (0);
	}
	return (1);
}
