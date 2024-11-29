/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_prepare_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:29:37 by ateca             #+#    #+#             */
/*   Updated: 2024/11/22 14:41:23 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**prepare_args(char *executable_path, char **original_args)
{
	int		i;
	int		arg_count;
	char	**new_args;

	arg_count = 0;
	while (original_args && original_args[arg_count])
		arg_count++;
	new_args = malloc((arg_count + 2) * sizeof(char *));
	if (!new_args)
	{
		perror("minishell: malloc failed");
		exit(1);
	}
	new_args[0] = ft_strdup(executable_path);
	if (!new_args[0])
	{
		perror("minishell: malloc failed");
		free(new_args);
		exit(1);
	}
	i = -1;
	while (++i < arg_count)
		new_args[i + 1] = original_args[i];
	new_args[arg_count + 1] = NULL;
	return (new_args);
}

char	*get_env_(char **path, t_env **env)
{
	(*path) = get_env_value("PATH", env);
	return (*path);
}

char	*absolute_relative_path(char *command)
{
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	else
	{
		printf("minishell: %s: %s\n", strerror(errno), command);
		exit(1);
	}
}

char	*find_executable_path(char *command, t_env **env)
{
	char	*dir;
	char	*path;
	char	*path_copy;
	char	*next_path;
	char	*exec_path;

	if (ft_strchr(command, '/') != NULL)
		return (absolute_relative_path(command));
	if (!get_env_(&path, env))
		return (NULL);
	path_copy = ft_strdup(path);
	dir = ft_strtok(path_copy, ':', &next_path);
	while (dir)
	{
		exec_path = ft_strjoin_delimiter(dir, '/', command);
		if (access(exec_path, F_OK) == 0 && access(exec_path, X_OK) == 0)
		{
			free(path_copy);
			return (exec_path);
		}
		free(exec_path);
		dir = ft_strtok(NULL, ':', &next_path);
	}
	free(path_copy);
	return (NULL);
}
