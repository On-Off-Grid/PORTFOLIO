/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:30:06 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:30:07 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_declare_var(char *env_var)
{
	char	*eq;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	eq = ft_strchr(env_var, '=');
	if (eq)
	{
		write(STDOUT_FILENO, env_var, eq - env_var);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(eq + 1, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putstr_fd(env_var, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static int	export_without_args(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		print_declare_var(envp[i]);
		i++;
	}
	return (0);
}

static int	validate_export_arg(char *arg)
{
	char	**split;

	if (!arg || ft_strcmp(arg, "=") == 0 || arg[0] == '=')
	{
		if (arg)
			export_error(arg);
		else
			export_error("");
		return (0);
	}
	split = ft_split(arg, '=');
	if (!split || !split[0])
	{
		export_error(arg);
		free_split(split);
		return (0);
	}
	return (check_identifier_validity(arg, split));
}

int	builtin_export(char **argv, t_shell_ctx *ctx)
{
	char	**new_envp;
	int		i;

	if (!argv[1])
		return (export_without_args(ctx->current_env));
	i = 1;
	while (argv[i])
	{
		if (!validate_export_arg(argv[i]))
			return (1);
		new_envp = add_export_var(argv, i, &ctx->current_env);
		if (should_free_env(ctx))
			free_split(ctx->current_env);
		update_shell_env(ctx, new_envp);
		i++;
	}
	return (0);
}
