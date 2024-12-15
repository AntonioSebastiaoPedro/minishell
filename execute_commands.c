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

void	restore_stdio(int original_stdin, int original_stdout, int status,
	t_env **envp)
{
	(void)envp;
	g_exit_status = status;
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

void	wait_for_processes(pid_t *pids, int num_commands, int *status)
{
	int	i;
	int	local_status;

	i = 0;
	local_status = 0;
	while (i < num_commands)
	{
		if (pids[i] != -1)
		{
			waitpid(pids[i], &local_status, 0);
			if (WIFEXITED(local_status))
				*status = WEXITSTATUS(local_status);
		}
		i++;
	}
	signal(SIGINT, handle_sigint);
}


/*void	wait_for_processes(pid_t *pids, int num_commands, int *status)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		if (pids[i] != -1)
		{
			waitpid(pids[i], status, 0);
		}
		i++;
	}
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	signal(SIGINT, handle_sigint);
}*/

int	ft_lstsize_command(t_command *head)
{
	int	len;

	len = 0;
	while (head)
	{
		len++;
		head = head->next;
	}
	return (len);
}

void	execute_commands(t_command *cmd, t_env **envp)
{
	pid_t			*pids;
	t_status_cmd	st;

	st.env = envp;
	st.status = 0;
	st.original_stdin = dup(STDIN_FILENO);
	st.original_stdout = dup(STDOUT_FILENO);
	st.num_commands = ft_lstsize_command(cmd);
	pids = malloc(sizeof(pid_t) * st.num_commands);
	if (!pids)
	{
		perror("minishell: malloc failed");
		restore_stdio(st.original_stdin, st.original_stdout, st.status, st.env);
		return ;
	}
	if (exec_builtin_exec_external(cmd, pids, &st) == -1)
	{
		free(pids);
		restore_stdio(st.original_stdin, st.original_stdout, st.status, st.env);
		return ;
	}
	if (cmd->command != NULL && !is_builtin(cmd->command))
		wait_for_processes(pids, st.num_commands, &st.status);
	restore_stdio(st.original_stdin, st.original_stdout, st.status, st.env);
	free(pids);
}
