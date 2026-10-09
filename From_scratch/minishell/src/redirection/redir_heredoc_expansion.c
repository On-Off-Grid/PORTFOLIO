/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:37:49 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:37:50 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Helper function to check if delimiter has quotes */
int	has_quotes(char *delimiter)
{
	int	len;

	if (!delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (len < 2)
		return (0);
	return ((delimiter[0] == '"' && delimiter[len - 1] == '"')
		|| (delimiter[0] == '\'' && delimiter[len - 1] == '\''));
}

/* Remove quotes from delimiter for comparison */
char	*remove_quotes(char *delimiter)
{
	int	len;

	if (!has_quotes(delimiter))
		return (ft_strdup(delimiter));
	len = ft_strlen(delimiter);
	return (ft_substr(delimiter, 1, len - 2));
}

char	*evaluate_heredoc_line(char *line, char *delimiter)
{
	(void)delimiter;
	return (ft_strdup(line));
}
