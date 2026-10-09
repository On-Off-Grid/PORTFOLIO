/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:36:42 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:36:43 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = safe_malloc(sizeof(t_cmd));
	cmd->argv = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->next = NULL;
	return (cmd);
}

char	*merge_first_token(char *merged, t_token **token)
{
	char	*temp;

	if (*token && ((*token)->type == WORD || (*token)->type == SQUOTE
			|| (*token)->type == DQUOTE))
	{
		temp = merged;
		merged = ft_strjoin(merged, (*token)->value);
		free(temp);
		*token = (*token)->next;
	}
	return (merged);
}

char	*merge_remaining_tokens(char *merged, t_token **token)
{
	char	*temp;

	while (*token && ((*token)->type == WORD || (*token)->type == SQUOTE
			|| (*token)->type == DQUOTE) && !(*token)->has_leading_space)
	{
		temp = merged;
		merged = ft_strjoin(merged, (*token)->value);
		free(temp);
		*token = (*token)->next;
	}
	return (merged);
}

char	*merge_adjacent_tokens(t_token **current)
{
	char	*merged;

	merged = ft_strdup("");
	merged = merge_first_token(merged, current);
	merged = merge_remaining_tokens(merged, current);
	return (merged);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_argv;
	int		i;

	count = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = safe_malloc((count + 2) * sizeof(char *));
	i = 0;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[count] = arg;
	new_argv[count + 1] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}
