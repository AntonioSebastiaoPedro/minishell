/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:06:04 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/10 14:37:29 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_execute_command_3 = 1;

void	handle_sigint_heredoc(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	exit(0);
}

void	handle_sigterm_heredoc(int signum)
{
	(void)signum;
	exit(1);
}

int	handle_heredoc(char *delimiter)
{
	int		pipe_fds[2];
	int		write_check;
	char	*line;

	write_check = 0;
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGTERM, handle_sigterm_heredoc);
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			if (write_check == 0)
				exit(1);
			break ;
		}
		write(pipe_fds[1], line, strlen(line));
		write(pipe_fds[1], "\n", 1);
		write_check = 1;
		free(line);
		g_execute_command_3 = 1;
	}
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	return (getpid());
}
