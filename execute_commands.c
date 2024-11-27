/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:07:48 by ateca             #+#    #+#             */
/*   Updated: 2024/11/18 11:07:53 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdio(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

int	execute_command(t_command *cmd, int original_stdout, char **envp)
{
	if (cmd->command != NULL && is_builtin(cmd->command))
	{
		exec_builtin(cmd, original_stdout);
	}
	else
	{
		return (execute_external_command(cmd, envp));
	}
	return (0);
}

void	expand_command_args(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			cmd->args[i] = expand_variables(cmd->args[i]);
			i++;
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

void	execute_commands(t_command *cmd, char **envp)
{
	int	result;
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	while (cmd != NULL)
	{
		if (setup_pipes(cmd) == -1)
			break ;
		expand_command_args(cmd);
		result = handle_redirections(&cmd, original_stdout);
		if (result == -2)
			break ;
		else if (result == -3)
		{
			cmd = cmd->next;
			continue ;
		}
		if (execute_command(cmd, original_stdout, envp) == -1)
			break ;
		cmd = cmd->next;
	}
	restore_stdio(original_stdin, original_stdout);
}
