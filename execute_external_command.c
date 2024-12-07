/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:45:18 by ateca             #+#    #+#             */
/*   Updated: 2024/11/22 14:41:57 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(t_command *cmd)
{
	if (cmd->read_pipe_fd != -1)
		close(cmd->read_pipe_fd);
	if (cmd->write_pipe_fd != -1)
		close(cmd->write_pipe_fd);
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

int	create_processes(t_command **cmd, t_env **envp, pid_t *pids, int num_cmds)
{
	int	i;

	i = 0;
	while (*cmd != NULL && i < num_cmds)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("minishell: fork failed");
			pids[i] = -1;
			return (-1);
		}
		if (pids[i] == 0)
		{
			handle_pipes_in_child(*cmd);
			execute_child_process(*cmd, envp);
		}
		handle_parent_process(*cmd);
		*cmd = (*cmd)->next;
		i++;
	}
	if ((*cmd) == NULL)
		return (-1);
	return (0);
}

int	execute_external_command(t_command **cmd, t_env **envp)
{
	int		num_commands;
	int		result;
	int		j;
	pid_t	*pids;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_sigint_external_command);
	num_commands = ft_lstsize_command(*cmd);
	pids = malloc(sizeof(pid_t) * num_commands);
	if (!pids)
	{
		perror("minishell: malloc failed");
		return (-1);
	}
	result = create_processes(cmd, envp, pids, num_commands);
	j = 0;
	while (j < num_commands && pids[j] != -1)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
	free(pids);
	signal(SIGINT, handle_sigint);
	return (result);
}
