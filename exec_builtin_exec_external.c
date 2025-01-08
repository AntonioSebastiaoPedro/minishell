/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_exec_external.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:45:18 by ateca             #+#    #+#             */
/*   Updated: 2024/12/10 12:40:47 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(t_command *cmd)
{
	if (cmd->read_pipe_fd != -1)
	{
		close(cmd->read_pipe_fd);
		cmd->read_pipe_fd = -1;
	}
	if (cmd->write_pipe_fd != -1)
	{
		close(cmd->write_pipe_fd);
		cmd->write_pipe_fd = -1;
	}
}

void	execute_child_process(t_command *cmd, t_env **envp)
{
	char	**new_args;
	char	*executable_path;
	char	**env_array;

	executable_path = find_executable_path(cmd->command, envp);
	print_check_cmd(executable_path, cmd);
	new_args = prepare_args(executable_path, cmd->args);
	if (!new_args)
	{
		perror("minishell: malloc failed");
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
	if (cmd->write_pipe_fd != -1 && !cmd->output_redir)
	{
		dup2(cmd->write_pipe_fd, STDOUT_FILENO);
		close(cmd->write_pipe_fd);
	}
	if (cmd->read_pipe_fd != -1 && !cmd->input_redir)
	{
		dup2(cmd->read_pipe_fd, STDIN_FILENO);
		close(cmd->read_pipe_fd);
	}
	if (cmd->next && cmd->next->read_pipe_fd != -1)
		close(cmd->next->read_pipe_fd);
	if (cmd->next && cmd->next->write_pipe_fd != -1)
		close(cmd->next->write_pipe_fd);
}

int	create_processes(t_command *cmd, pid_t *pids, int i, t_status_cmd *st)
{
	if (cmd != NULL && cmd->command != NULL && is_builtin(cmd->command))
	{
		st->status = exec_builtin(cmd, st->original_stdout, st->env);
	}
	else if (cmd != NULL && cmd->command != NULL)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, handle_sigint_external_command);
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("minishell: fork failed");
			pids[i] = -1;
			return (-1);
		}
		if (pids[i] == 0)
		{
			handle_pipes_in_child(cmd);
			execute_child_process(cmd, st->env);
		}
		handle_parent_process(cmd);
	}
	return (0);
}

int	exec_builtin_exec_external(t_command *cmd, pid_t *pids, t_status_cmd *st)
{
	int			i;
	int			result;
	t_command	*current;

	i = 0;
	current = cmd;
	while (current != NULL && i < st->num_commands)
	{
		if (setup_pipes(current) == -1)
			return (-1);
		result = handle_redirections(&current, st, pids, &i);
		if (result == -2)
			return (-1);
		else if (result == -3)
			continue ;
		if (create_processes(current, pids, i, st) == -1)
			return (-1);
		if (current)
			current = current->next;
		i++;
	}
	return (0);
}
