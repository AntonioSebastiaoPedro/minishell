/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_stdin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:21:15 by ateca             #+#    #+#             */
/*   Updated: 2024/11/28 15:04:05 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_isspace(char *line, int i)
{
	i++;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	child_process(int *pipe_fd, t_token **tokens, t_env **env)
{
	char	*line;

	close(pipe_fd[0]);
	signal(SIGINT, handle_sigint_heredoc);
	*tokens = add_token(*tokens, "|", 0);
	while (1)
	{
		line = readline("> ");
		if (line && (check_isspace(line, -1) || ft_strcmp(line, "") == 0))
		{
			free(line);
			continue ;
		}
		if (line == NULL)
		{
			write(2, "minishell: ", 11);
			write(2, "syntax error: unexpected end of file\n", 37);
			write(2, "exit\n", 5);
			exit_free_reso_pipe(2, tokens, env);
		}
		write(pipe_fd[1], line, ft_strlen(line));
		close(pipe_fd[1]);
		free(line);
		exit_free_reso_pipe(0, tokens, env);
	}
}

void	read_from_pipe(int *pipe_fd, t_token **tokens, t_env **env)
{
	char	*new_line;
	int		bytes;

	new_line = malloc(2097152 * sizeof(char));
	if (!new_line)
	{
		perror("malloc failed");
		exit(1);
	}
	bytes = read(pipe_fd[0], new_line, 2097152);
	if (bytes >= 0 && bytes < 2097152)
	{
		new_line[bytes] = '\0';
		tokenize(new_line, tokens, env, 0);
	}
	else
		perror("Read error or size exceeded");
	free(new_line);
	close(pipe_fd[0]);
}

void	parent_process(int status, t_token **tokens, int *pipe_fd, t_env **env)
{
	close(pipe_fd[1]);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
	{
		g_exit_status = WEXITSTATUS(status);
		exit_free_reso_pipe(g_exit_status, tokens, env);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		free_tokens(*tokens);
		g_exit_status = WEXITSTATUS(status);
		*tokens = NULL;
	}
	else
		read_from_pipe(pipe_fd, tokens, env);
}

void	handle_pipe_stdin(char *line, t_token **tokens, int *i, t_env **env)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	signal(SIGINT, SIG_IGN);
	add_token(*tokens, "|", 0);
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
		child_process(pipe_fd, tokens, env);
	else if (pid < 0)
	{
		*tokens = NULL;
		*i = ft_strlen(line);
		signal(SIGINT, handle_sigint);
		perror("fork failed");
	}
	else
	{
		*i = ft_strlen(line);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sigint);
		parent_process(status, tokens, pipe_fd, env);
	}
}
