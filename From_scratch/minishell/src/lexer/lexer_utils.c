/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:36:16 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:36:18 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*init_token_list(void)
{
	return (NULL);
}

void	add_token(t_token **head, t_token_type type, char *value,
	int has_space)
{
	t_token	*new_token;
	t_token	*current;

	new_token = safe_malloc(sizeof(t_token));
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->has_leading_space = has_space;
	new_token->next = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

int	skip_whitespace(const char *line, int *i)
{
	int	has_space;

	has_space = 0;
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
	{
		has_space = 1;
		(*i)++;
	}
	return (has_space);
}
