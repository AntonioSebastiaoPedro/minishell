/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:11:19 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/18 12:30:10 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_execute_command_2 = 1;

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

char	*find_executable_path(char *command)
{
	char	*dir;
	char	*path;
	char	*path_copy;
	char	*next_path;
	char	*exec_path;

	if (strchr(command, '/') != NULL)
		return (absolute_relative_path(command));
	path = getenv("PATH");
	if (!path)
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
		dir = ft_strtok(NULL, ':', &next_path);
	}
	free(path_copy);
	return (NULL);
}

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
		perror("malloc failed");
		exit(1);
	}
	new_args[0] = ft_strdup(executable_path);
	if (!new_args[0])
	{
		perror("malloc failed");
		free(new_args);
		exit(1);
	}
	i = -1;
	while (++i < arg_count)
		new_args[i + 1] = original_args[i];
	new_args[arg_count + 1] = NULL;
	return (new_args);
}

int	execute_external_command(t_command *cmd, t_env **envp, int *status)
{
	char	**new_args;
	char	*executable_path;
	char	**env_dup;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		executable_path = find_executable_path(cmd->command);
		if (!executable_path)
		{
			printf("minishell: command not found: %s\n", cmd->command);
			*status = 1;
			exit (1);
		}
		new_args = prepare_args(executable_path, cmd->args);
		if (!new_args)
		{
			perror("prepare_args failed");
			*status = 1;
			exit (1);
		}
		env_dup = env_list_to_array(*envp);
		execve(executable_path, new_args, env_dup);
		ft_freearray(env_dup);
		free(executable_path);
		perror("minishell");
		*status = errno;
		exit (errno);
	}
	else if (pid < 0)
	{
		perror("fork failed");
		*status = 1;
		return (1);
	}
	else
		waitpid(pid, status, 0);
	return (*status);
}

void	execute_commands(t_command *cmd, t_env **env)
{
	int	i;
	int	pid_heredoc;
	int	original_stdin;
	int	original_stdout;
	int	status;

	pid_heredoc = 0;
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	while (cmd)
	{
		i = -1;
		if (cmd->args)
		{
			g_execute_command_2 = 1;
			while (cmd->args[++i])
				cmd->args[i] = expand_variables(cmd->args[i], cmd, &i, env);
		}
		pid_heredoc = handle_redirections(cmd);
		if (pid_heredoc == -1)
		{
			cmd = cmd->next;
			continue ;
		}
		if (is_builtin(cmd->command))
		{
			g_execute_command_2 = 1;
			exec_builtin(cmd, env, &status);
			update_envvar(env, "X", ft_itoa(status));
		}
		else if (g_execute_command_2 == 1)
		{
			execute_external_command(cmd, env, &status);
			update_envvar(env, "X", ft_itoa(status));
			if (pid_heredoc != 0)
				kill(pid_heredoc, SIGTERM);
		}
		else
			g_execute_command_2 = 1;
		cmd = cmd->next;
	}
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
