/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:04:27 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:04:29 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char **envp, const char *key)
{
	int		i;
	int		key_len;
	char	*equals;

	if (!envp || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		equals = ft_strchr(envp[i], '=');
		if (equals && (equals - envp[i]) == key_len)
		{
			if (ft_strncmp(envp[i], key, key_len) == 0)
				return (equals + 1);
		}
		i++;
	}
	return (NULL);
}

int	env_var_exists(char **envp, const char *key)
{
	int		i;
	int		key_len;
	char	*equals;

	if (!envp || !key)
		return (0);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		equals = ft_strchr(envp[i], '=');
		if (equals && (equals - envp[i]) == key_len)
		{
			if (ft_strncmp(envp[i], key, key_len) == 0)
				return (1);
		}
		else if (!equals && ft_strcmp(envp[i], key) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**allocate_new_env(char **envp, int *count)
{
	char	**new_envp;
	int		i;

	*count = 0;
	while (envp[*count])
		(*count)++;
	new_envp = malloc(sizeof(char *) * (*count + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < *count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

char	*create_env_var_string(const char *key, const char *value)
{
	char	*temp;
	char	*result;

	if (value == NULL)
		return (ft_strdup(key));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	if (value)
		result = ft_strjoin(temp, value);
	else
		result = ft_strjoin(temp, "");
	free(temp);
	return (result);
}
