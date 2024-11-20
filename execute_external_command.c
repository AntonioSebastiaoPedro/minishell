/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:45:18 by ateca             #+#    #+#             */
/*   Updated: 2024/11/18 11:45:19 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(t_command *cmd, pid_t pid)
{
	waitpid(pid, NULL, 0);
	if (cmd->read_pipe_fd != -1)
		close(cmd->read_pipe_fd);
	if (cmd->write_pipe_fd != -1)
		close(cmd->write_pipe_fd);
	signal(SIGINT, handle_sigint);
}

void	execute_child_process(t_command *cmd, char **envp)
{
	char	**new_args;
	char	*executable_path;
	char	*msg;

	executable_path = find_executable_path(cmd->command);
	if (!executable_path)
	{
		msg = ": command not found";
		write(2, cmd->command, ft_strlen(cmd->command));
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
		exit(127);
	}
	new_args = prepare_args(executable_path, cmd->args);
	if (!new_args)
	{
		perror("minishell: prepare_args failed");
		exit(1);
	}
	execve(executable_path, new_args, envp);
	free(executable_path);
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

int	execute_external_command(t_command *cmd, char **envp)
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
		handle_parent_process(cmd, pid);
	}
	return (0);
}
