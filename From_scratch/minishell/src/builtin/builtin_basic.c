/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:29:58 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:29:59 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_echo(char **argv)
{
	int		i;
	int		newline;

	newline = 1;
	i = 1;
	while (argv[i] && ft_strcmp_echo(argv[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

static int	validate_cd_args(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	return (0);
}

static char	*get_cd_path(char **argv, char **envp)
{
	char	*path;

	(void)envp;
	if (!argv[1])
		path = getenv("HOME");
	else
		path = argv[1];
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (NULL);
	}
	return (path);
}

int	builtin_cd(char **argv, char **envp)
{
	char	*path;

	if (validate_cd_args(argv) != 0)
		return (1);
	path = get_cd_path(argv, envp);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}
