/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:04:24 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:04:25 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	should_keep_env_var(char *env_var, const char *key, int key_len)
{
	return (!(ft_strncmp(env_var, key, key_len)
			== 0 && env_var[key_len] == '='));
}

static char	**allocate_env_array(char **envp)
{
	int		count;
	char	**new_envp;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * count);
	return (new_envp);
}

static void	copy_filtered_env_vars(char **envp, char **new_envp,
	const char *key, int key_len)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	while (envp[count])
		count++;
	i = 0;
	j = 0;
	while (i < count)
	{
		if (should_keep_env_var(envp[i], key, key_len))
		{
			new_envp[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
}

char	**env_remove_var(char **envp, const char *key)
{
	char	**new_envp;
	int		key_len;

	if (!envp || !key)
		return (NULL);
	new_envp = allocate_env_array(envp);
	if (!new_envp)
		return (NULL);
	key_len = ft_strlen(key);
	copy_filtered_env_vars(envp, new_envp, key, key_len);
	return (new_envp);
}
