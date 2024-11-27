/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:01:15 by ateca             #+#    #+#             */
/*   Updated: 2024/11/18 14:01:18 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_file_input_redirection(t_command *cmd)
{
	int	fd_read;

	fd_read = open(cmd->input_redir, O_RDONLY);
	if (fd_read < 0)
	{
		print_error_redirection_file(cmd->input_redir);
		if (cmd->next != NULL && expects_stdin(cmd->next->command))
			return (-2);
		return (-3);
	}
	dup2(fd_read, STDIN_FILENO);
	close(fd_read);
	return (0);
}

int	handle_heredoc_parent_process(t_command *cmd, pid_t pid)
{
	int	status;

	close(cmd->write_pipe_fd);
	dup2(cmd->read_pipe_fd, STDIN_FILENO);
	close(cmd->read_pipe_fd);
	waitpid(pid, &status, 0);
	cmd->write_pipe_fd = -1;
	cmd->read_pipe_fd = -1;
	signal(SIGINT, handle_sigint);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		if (cmd->next != NULL)
		{
			if (cmd->next->output_redir)
			{
				cmd->next->heredoc = 1;
				cmd->next->command = ft_strdup(cmd->command);
			}
			return (-3);
		}
		return (0);
	}
	return (-2);
}

void	handle_heredoc(t_command *cmd)
{
	int		write_check;
	char	*line;
	char	*delimiter;

	write_check = 0;
	delimiter = cmd->input_redir;
	signal(SIGINT, handle_sigint_heredoc);
	close(cmd->read_pipe_fd);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			if (write_check == 0)
				exit(0);
			break ;
		}
		write_check = 1;
		write(cmd->write_pipe_fd, line, ft_strlen(line));
		write(cmd->write_pipe_fd, "\n", 1);
		free(line);
	}
	close(cmd->write_pipe_fd);
	exit(0);
}

int	handle_heredoc_redirection(t_command *cmd, int fd_stdout)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		if (!isatty(STDOUT_FILENO))
		{
			dup2(fd_stdout, STDOUT_FILENO);
			close(fd_stdout);
		}
		handle_heredoc(cmd);
	}
	else if (pid < 0)
	{
		signal(SIGINT, handle_sigint);
		perror("minishell: fork failed");
		return (-2);
	}
	return (handle_heredoc_parent_process(cmd, pid));
}

int	handle_input_redirection(t_command *cmd, int fd_stdout)
{
	if (cmd->heredoc)
		return (handle_heredoc_redirection(cmd, fd_stdout));
	else
		return (handle_file_input_redirection(cmd));
}
