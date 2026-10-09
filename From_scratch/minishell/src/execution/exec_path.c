/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:34:38 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:34:39 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>
#include <sys/stat.h>

static char	*handle_absolute_path(char *cmd)
{
	struct stat	st;

	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			errno = EISDIR;
			return (NULL);
		}
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		errno = EACCES;
		return (NULL);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (NULL);
	}
}

static char	*search_in_path_dirs(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(cmd));
	path_env = get_env_value(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_path_dirs(cmd, paths);
	free(paths);
	return (result);
}

int	handle_cmd_not_found(t_cmd *cmd, char *cmd_path)
{
	if (!cmd_path)
	{
		if (errno == EISDIR)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putendl_fd(": Is a directory", 2);
			return (126);
		}
		else if (errno == EACCES)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			return (126);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putendl_fd(": command not found", 2);
			return (127);
		}
	}
	return (0);
}
