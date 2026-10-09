/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_modify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <aybareic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:04:33 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:51:18 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**env_add_var(char **envp, const char *key, const char *value)
{
	char	**new_envp;
	int		count;

	new_envp = allocate_new_env(envp, &count);
	if (!new_envp)
		return (NULL);
	new_envp[count] = create_env_var_string(key, value);
	new_envp[count + 1] = NULL;
	return (new_envp);
}

static char	*create_updated_var(const char *key, const char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

static int	should_update_var(char *env_var, const char *key, int key_len)
{
	int	key_match;
	int	exact_match;

	key_match = (ft_strncmp(env_var, key, key_len) == 0
			&& (env_var[key_len] == '=' || env_var[key_len] == '\0'));
	exact_match = ft_strcmp(env_var, key) == 0;
	return (key_match || exact_match);
}

char	**env_update_var(char **envp, const char *key, const char *value)
{
	char	**new_envp;
	int		count;
	int		key_len;
	int		i;

	new_envp = allocate_new_env(envp, &count);
	if (!new_envp)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (i < count)
	{
		if (should_update_var(new_envp[i], key, key_len))
		{
			free(new_envp[i]);
			if (value == NULL)
				new_envp[i] = ft_strdup(key);
			else
				new_envp[i] = create_updated_var(key, value);
			break ;
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}
