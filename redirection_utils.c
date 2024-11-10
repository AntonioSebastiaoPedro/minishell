/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:04:11 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/10 14:20:04 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_execute_command = 1;

int	handle_output_redirection(t_command *cmd)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append == 1)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->output_redir, flags, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", cmd->output_redir, strerror(errno));
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_input_redirection(t_command *cmd)
{
	int		fd;
	int		status;
	pid_t	pid;

	if (cmd->heredoc)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			return (handle_heredoc(cmd->input_redir));
		else if (pid < 0)
		{
			signal(SIGINT, handle_sigint);
			perror("fork failed");
			return (-1);
		}
		else
		{
			waitpid(pid, &status, 0);
			signal(SIGINT, handle_sigint);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				g_execute_command = 1;
				return (-1);
			}
			else
			{
				if (cmd->next != NULL)
					g_execute_command = 0;
				return (-1);
			}
		}
	}
	else
	{
		fd = open(cmd->input_redir, O_RDONLY);
		if (fd < 0)
		{
			printf("minishell: %s: %s\n", cmd->input_redir, strerror(errno));
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	handle_redirections(t_command *cmd)
{
	if (cmd->input_redir != NULL)
		return (handle_input_redirection(cmd));
	else if (cmd->output_redir != NULL)
		return (handle_output_redirection(cmd));
	return (0);
}
