/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:45:18 by ateca             #+#    #+#             */
/*   Updated: 2024/12/07 17:30:08 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(t_command *cmd, pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (cmd->read_pipe_fd != -1)
		close(cmd->read_pipe_fd);
	if (cmd->write_pipe_fd != -1)
		close(cmd->write_pipe_fd);
	signal(SIGINT, handle_sigint);
}

void	check_cmd(char *exec_path, t_command *cmd)
{
	char	*msg;

	if (!exec_path)
	{
		msg = ": command not found";
		write(2, cmd->command, ft_strlen(cmd->command));
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
		exit(127);
	}
}

void	execute_child_process(t_command *cmd, t_env **envp)
{
	char	**new_args;
	char	*executable_path;
	char	**env_array;

	executable_path = find_executable_path(cmd->command, envp);
	check_cmd(executable_path, cmd);
	new_args = prepare_args(executable_path, cmd->args);
	if (!new_args)
	{
		perror("minishell: prepare_args failed");
		exit(1);
	}
	env_array = env_list_to_array(*envp);
	execve(executable_path, new_args, env_array);
	free(executable_path);
	ft_freearray(env_array);
	perror("minishell");
	exit(errno);
}

void	handle_pipes_in_child(t_command *cmd)
{
	if (cmd->write_pipe_fd != -1)
	{
		dup2(cmd->write_pipe_fd, STDOUT_FILENO);
		close(cmd->write_pipe_fd);
	}
	if (cmd->read_pipe_fd != -1)
	{
		dup2(cmd->read_pipe_fd, STDIN_FILENO);
		close(cmd->read_pipe_fd);
	}
}

int	execute_external_command(t_command *cmd, t_env **envp, int *status)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_sigint_external_command);
	pid = fork();
	if (pid == 0)
	{
		handle_pipes_in_child(cmd);
		execute_child_process(cmd, envp);
	}
	else if (pid < 0)
	{
		perror("minishell: fork failed");
		return (-1);
	}
	else
	{
		handle_parent_process(cmd, pid, status);
	}
	return (0);
}
