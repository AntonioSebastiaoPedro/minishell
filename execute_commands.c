/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:11:19 by ansebast          #+#    #+#             */
/*   Updated: 2024/12/07 17:50:21 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdio(int original_stdin, int original_stdout, int status,
		t_env **envp)
{
	char	*char_status;

	char_status = ft_itoa(status);
	update_envvar(envp, "XDG_CMD_STATUS", char_status);
	free(char_status);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

/*int	execute_command(t_command **cmd, int original_stdout, t_env **envp,
		int *status)
{
	char	*char_status;
	int		result;

	result = 0;
	if ((*cmd)->command != NULL && is_builtin((*cmd)->command))
	{
		*status = exec_builtin((*cmd), original_stdout, envp);
	}
	else
	{
		result = execute_external_command(cmd, envp, status);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
	char_status = ft_itoa(*status);
	update_envvar(envp, "XDG_CMD_STATUS", char_status);
	free(char_status);
	return (result);
}*/

void	expand_command_args(t_command *cmd, t_env **env)
{
	int	i;
	int	arg_pos;

	i = 0;
	arg_pos = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			cmd->args[i] = expand_variables(cmd->args[i], cmd, &arg_pos, env);
			i++;
			arg_pos++;
		}
	}
}

int	setup_pipes(t_command *cmd)
{
	int	pipe_fd[2];

	if (cmd->next != NULL || (cmd->command && cmd->input_redir && cmd->heredoc))
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("minishell: pipe failed");
			return (-1);
		}
		if (cmd->next != NULL)
		{
			cmd->write_pipe_fd = pipe_fd[1];
			cmd->next->read_pipe_fd = pipe_fd[0];
		}
		else if (cmd->command && cmd->input_redir && cmd->heredoc)
		{
			cmd->write_pipe_fd = pipe_fd[1];
			cmd->read_pipe_fd = pipe_fd[0];
		}
	}
	return (0);
}

void	execute_commands(t_command *cmd, t_env **envp)
{
	int		original_stdin;
	int		original_stdout;
	int		status = 0;
	int		num_commands;
	pid_t	*pids;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	num_commands = ft_lstsize_command(cmd);
	pids = malloc(sizeof(pid_t) * num_commands);
	if (!pids)
	{
		perror("minishell: malloc failed");
		restore_stdio(original_stdin, original_stdout, status, envp);
		return ;
	}
	if (create_processes_(cmd, envp, pids, num_commands, original_stdout) == -1)
	{
		free(pids);
		restore_stdio(original_stdin, original_stdout, status, envp);
		return ;
	}
	for (int i = 0; i < num_commands; i++)
	{
		if (pids[i] != -1)
			waitpid(pids[i], &status, 0);
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);

	char *char_status = ft_itoa(status);
	update_envvar(envp, "XDG_CMD_STATUS", char_status);
	free(char_status);
	free(pids);
	restore_stdio(original_stdin, original_stdout, status, envp);
}

/*void	execute_commands(t_command *cmd, t_env **envp)
{
	int	original_stdin;
	int	original_stdout;
	int	status;
	int	result;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	while (cmd != NULL)
	{
		if (setup_pipes(cmd) == -1)
			break ;
		expand_command_args(cmd, envp);
		result = handle_redirections(&cmd, original_stdout, &status);
		if (result == -2)
			break ;
		else if (result == -3)
		{
			cmd = cmd->next;
			continue ;
		}
		if (execute_command(&cmd, original_stdout, envp, &status) == -1)
			break ;
		cmd = cmd->next;
	}
	restore_stdio(original_stdin, original_stdout, status, envp);
}*/
