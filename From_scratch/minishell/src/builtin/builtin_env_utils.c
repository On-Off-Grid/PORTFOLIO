/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:30:16 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:30:22 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	if (ft_strcmp(arg, "=") == 0)
		ft_putstr_fd("=", 2);
	else
		ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	check_identifier_validity(char *arg, char **split)
{
	char	*identifier;

	identifier = split[0];
	if (!is_valid_identifier(identifier))
	{
		export_error(arg);
		free_split(split);
		return (0);
	}
	free_split(split);
	return (1);
}

static char	**handle_export_no_equals(char **envp, char *var_name)
{
	if (env_var_exists(envp, var_name))
		return (envp);
	else
		return (env_add_var(envp, var_name, NULL));
}

static char	**handle_export_with_equals(char **envp, char *var_name,
	char *value)
{
	if (env_var_exists(envp, var_name))
		return (env_update_var(envp, var_name, value));
	else
		return (env_add_var(envp, var_name, value));
}

char	**add_export_var(char **argv, int i, char ***envp)
{
	char	**split;
	char	**new_envp;
	int		has_equals;

	has_equals = (ft_strchr(argv[i], '=') != NULL);
	split = ft_split(argv[i], '=');
	if (!has_equals)
		new_envp = handle_export_no_equals(*envp, split[0]);
	else if (has_equals && !split[1])
		new_envp = handle_export_with_equals(*envp, split[0], "");
	else
		new_envp = handle_export_with_equals(*envp, split[0], split[1]);
	free_split(split);
	return (new_envp);
}
