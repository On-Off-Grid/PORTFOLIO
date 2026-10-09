/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:36:58 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:36:59 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_redirections(t_redir *in, t_redir *out)
{
	t_redir	*current;
	int		result;

	current = in;
	while (current)
	{
		result = handle_input_redir(current);
		if (result != 0)
			return (result);
		current = current->next;
	}
	current = out;
	while (current)
	{
		result = handle_output_redir(current);
		if (result != 0)
			return (result);
		current = current->next;
	}
	return (0);
}
