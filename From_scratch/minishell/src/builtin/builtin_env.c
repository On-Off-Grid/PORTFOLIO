/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:30:03 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:30:03 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(char **argv, t_shell_ctx *ctx)
{
	char	**new_envp;
	int		i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			print_invalid_identifier("unset", argv[i]);
			i++;
			continue ;
		}
		if (env_var_exists(ctx->current_env, argv[i]))
		{
			new_envp = env_remove_var(ctx->current_env, argv[i]);
			if (should_free_env(ctx))
				free_split(ctx->current_env);
			update_shell_env(ctx, new_envp);
		}
		i++;
	}
	return (0);
}
