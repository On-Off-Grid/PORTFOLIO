/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:17:16 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:19:43 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_on_error(t_token *tokens, t_cmd *commands)
{
	if (tokens)
		free_tokens(tokens);
	if (commands)
		free_cmds(commands);
}

void	print_invalid_identifier(const char *cmd, const char *identifier)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	check_memory_allocation(void *ptr, const char *function_name)
{
	if (!ptr)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(function_name, 2);
		ft_putendl_fd(": memory allocation failed", 2);
		return (-1);
	}
	return (0);
}
