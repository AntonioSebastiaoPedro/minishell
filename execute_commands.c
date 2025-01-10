/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:11:19 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/09 17:55:29 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_processes(pid_t *pids, int num_commands, int *status)
{
	int	i;
	int	local_status;
	int	signal_code;

	i = 0;
	local_status = 0;
	while (i < num_commands)
	{
		if (pids[i] != -1)
		{
			waitpid(pids[i], &local_status, 0);
			if (WIFSIGNALED(local_status))
			{
				signal_code = WTERMSIG(local_status);
				if (*status == 0)
					*status = 128 + signal_code;
			}
			else if (WIFEXITED(local_status))
				if (*status == 0)
					*status = WEXITSTATUS(local_status);
		}
		i++;
	}
	signal(SIGINT, handle_sigint);
}

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

void	init_pids(pid_t *pids, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		pids[i] = -1;
		i++;
	}
}

t_status_cmd	init_status_cmd(t_env **envp, t_command *cmd)
{
	t_status_cmd	st;

	st.env = envp;
	st.status = 0;
	st.original_stdin = dup(STDIN_FILENO);
	st.original_stdout = dup(STDOUT_FILENO);
	st.num_commands = ft_lstsize_command(cmd);
	return (st);
}

void	execute_commands(t_command *cmd, t_env **envp, t_token **tokens)
{
	pid_t			*pids;
	t_status_cmd	st;

	st = init_status_cmd(envp, cmd);
	pids = malloc(sizeof(pid_t) * st.num_commands);
	st.tokens = tokens;
	st.pids = pids;
	if (!pids)
	{
		perror("minishell: malloc failed");
		restore_stdio(st.original_stdin, st.original_stdout, st.status);
		return ;
	}
	init_pids(pids, st.num_commands);
	if (exec_builtin_exec_external(cmd, pids, &st) == -1)
	{
		free(pids);
		restore_stdio(st.original_stdin, st.original_stdout, st.status);
		return ;
	}
	wait_for_processes(pids, st.num_commands, &st.status);
	restore_stdio(st.original_stdin, st.original_stdout, st.status);
	free(pids);
}
