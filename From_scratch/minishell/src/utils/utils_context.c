/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:40:35 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:40:36 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell_context(t_shell_ctx *ctx, char **envp)
{
	ctx->last_status = 0;
	ctx->original_env = envp;
	ctx->current_env = envp;
}

void	update_shell_status(t_shell_ctx *ctx, int status)
{
	ctx->last_status = status;
}

void	update_shell_env(t_shell_ctx *ctx, char **new_env)
{
	ctx->current_env = new_env;
}

int	should_free_env(t_shell_ctx *ctx)
{
	return (ctx->current_env != ctx->original_env);
}
