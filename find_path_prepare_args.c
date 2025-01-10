/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_prepare_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:29:37 by ateca             #+#    #+#             */
/*   Updated: 2025/01/10 10:51:09 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_valid_args(char **original_args)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (original_args && original_args[i])
	{
		if (ft_strcmp(original_args[i], " ") != 0)
			count++;
		i++;
	}
	return (count);
}

char	**prepare_args(char *executable_path, char **original_args)
{
	int		i;
	int		j;
	int		valid_arg_count;
	char	**new_args;

	valid_arg_count = count_valid_args(original_args);
	new_args = malloc((valid_arg_count + 2) * sizeof(char *));
	if (!new_args)
		return (NULL);
	new_args[0] = ft_strdup(ft_strrchr(executable_path, '/') + 1);
	if (!new_args[0])
	{
		free(new_args);
		return (NULL);
	}
	i = 0;
	j = 1;
	while (original_args && original_args[i])
	{
		if (ft_strcmp(original_args[i], " ") != 0)
			new_args[j++] = original_args[i];
		i++;
	}
	new_args[j] = NULL;
	return (new_args);
}

char	*get_env_(char **path, t_env **env, char *command)
{
	if (ft_strcmp(command, "") == 0)
		return (NULL);
	(*path) = get_env_value("PATH", env);
	return (*path);
}

char	*absolute_relative_path(t_command *path, t_status_cmd *st)
{
	struct stat	path_stat;

	if (stat(path->command, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, path->command, ft_strlen(path->command));
			write(2, ": Is a directory\n", 17);
			exit_free_resources(126, st);
		}
		if (access(path->command, X_OK) == 0)
			return (ft_strdup(path->command));
		else
		{
			write(2, "minishell: ", 11);
			write(2, path->command, ft_strlen(path->command));
			write(2, ": Permission denied\n", 20);
			exit_free_resources(126, st);
		}
	}
	print_error_no_such_file_or_directory(path->command);
	exit_free_resources(127, st);
	return (NULL);
}

char	*find_executable_path(t_command *command, t_status_cmd *st)
{
	char	*dir;
	char	*path;
	char	*path_copy;
	char	*next_path;
	char	*exec_path;

	if (ft_strchr(command->command, '/') != NULL)
		return (absolute_relative_path(command, st));
	if (!get_env_(&path, st->env, command->command))
		return (NULL);
	path_copy = ft_strjoin(path, ":");
	dir = ft_strtok(path_copy, ':', &next_path);
	while (dir)
	{
		exec_path = ft_strjoin_delimiter(dir, '/', command->command);
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
