/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:36:07 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:36:08 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token_type	check_double_operators(const char *str, int *len)
{
	if (str[0] == '<' && str[1] == '<')
	{
		*len = 2;
		return (OP_HEREDOC);
	}
	if (str[0] == '>' && str[1] == '>')
	{
		*len = 2;
		return (OP_APPEND);
	}
	return (WORD);
}

static t_token_type	check_single_operators(const char *str, int *len)
{
	if (str[0] == '<')
	{
		*len = 1;
		return (OP_IN);
	}
	if (str[0] == '>')
	{
		*len = 1;
		return (OP_OUT);
	}
	if (str[0] == '|')
	{
		*len = 1;
		return (PIPE);
	}
	return (WORD);
}

t_token_type	get_operator_type(const char *str, int *len)
{
	t_token_type	type;

	type = check_double_operators(str, len);
	if (type != WORD)
		return (type);
	return (check_single_operators(str, len));
}

void	process_operator(const char *line, int *i, t_token **tokens,
	int has_space)
{
	t_token_type	op_type;
	int				op_len;
	char			op_str[3];
	int				j;

	op_type = get_operator_type(&line[*i], &op_len);
	j = 0;
	while (j < op_len)
	{
		op_str[j] = line[*i + j];
		j++;
	}
	op_str[op_len] = '\0';
	add_token(tokens, op_type, op_str, has_space);
	*i += op_len;
}
