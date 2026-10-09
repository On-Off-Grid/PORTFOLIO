/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:40:27 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:40:28 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*expand_vars(char *str, char **envp, int last_status)
{
	char	*result;
	char	*expanded;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			expanded = expand_single_var(str, &i, envp, last_status);
			result = append_expansion(result, expanded);
		}
		else
		{
			result = append_char(result, str[i]);
			i++;
		}
	}
	return (result);
}

void	expand_token_vars(t_token *tokens, t_shell_ctx *ctx)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == WORD || current->type == DQUOTE)
		{
			expanded = expand_vars(current->value, ctx->current_env,
					ctx->last_status);
			if (expanded)
			{
				free(current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
}
