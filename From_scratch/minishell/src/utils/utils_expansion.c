/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:40:39 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:40:41 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*handle_status_var(int *i, int start, int last_status)
{
	*i = start + 1;
	return (ft_itoa(last_status));
}

static char	*handle_regular_var(char *str, int *i, int start, char **envp)
{
	char	*var_name;
	char	*var_value;
	int		len;

	len = 0;
	while (str[start + len] && (ft_isalnum(str[start + len])
			|| str[start + len] == '_'))
		len++;
	if (len == 0)
	{
		*i = start;
		return (ft_strdup("$"));
	}
	var_name = ft_substr(str, start, len);
	var_value = get_env_value(envp, var_name);
	free(var_name);
	*i = start + len;
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
}

char	*expand_single_var(char *str, int *i, char **envp, int last_status)
{
	int	start;

	start = *i + 1;
	if (str[start] == '?')
		return (handle_status_var(i, start, last_status));
	return (handle_regular_var(str, i, start, envp));
}

char	*append_expansion(char *result, char *expansion)
{
	char	*temp;

	temp = ft_strjoin(result, expansion);
	free(result);
	free(expansion);
	return (temp);
}

char	*append_char(char *result, char c)
{
	char	char_str[2];
	char	*temp;

	char_str[0] = c;
	char_str[1] = '\0';
	temp = ft_strjoin(result, char_str);
	free(result);
	return (temp);
}
