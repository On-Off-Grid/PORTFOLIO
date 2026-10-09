/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:36:03 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:36:04 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_meta_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_token	*lexer(const char *line)
{
	t_token	*tokens;
	int		i;
	int		has_space;

	if (!line)
		return (NULL);
	tokens = init_token_list();
	i = 0;
	while (line[i])
	{
		has_space = skip_whitespace(line, &i);
		if (!line[i])
			break ;
		if (line[i] == '\'' || line[i] == '"')
			handle_quotes(line, &i, &tokens, has_space);
		else if (is_meta_char(line[i]))
			process_operator(line, &i, &tokens, has_space);
		else
			handle_word(line, &i, &tokens, has_space);
	}
	return (tokens);
}
