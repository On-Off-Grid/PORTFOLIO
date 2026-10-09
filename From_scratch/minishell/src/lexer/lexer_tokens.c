/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:36:10 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:36:12 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quotes(const char *line, int *i, t_token **tokens,
	int has_space)
{
	char			quote;
	int				start;
	char			*content;
	t_token_type	type;

	quote = line[*i];
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
		(*i)++;
	content = ft_substr(line, start, *i - start);
	if (quote == '\'')
		type = SQUOTE;
	else
		type = DQUOTE;
	add_token(tokens, type, content, has_space);
	free(content);
	if (line[*i] == quote)
		(*i)++;
}

void	handle_word(const char *line, int *i, t_token **tokens, int has_space)
{
	int		start;
	char	*word;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '<' && line[*i] != '>' && line[*i] != '|'
		&& line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	word = ft_substr(line, start, *i - start);
	add_token(tokens, WORD, word, has_space);
	free(word);
}
