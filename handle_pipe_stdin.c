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

void	child_process(t_token **tokens, int *pipe_fd)
{
	char	*next_line;

	signal(SIGINT, handle_sigint_heredoc);
	*tokens = add_token(*tokens, "|", 0);
	next_line = readline("> ");
	if (next_line == NULL)
	{
		write(2, "minishell: ", 11);
		write(2, "syntax error: unexpected end of file\n", 37);
		write(2, "exit\n", 5);
		exit(1);
	}
	close(pipe_fd[0]);
	write(pipe_fd[1], next_line, ft_strlen(next_line));
	close(pipe_fd[1]);
	free(next_line);
	exit(0);
}

void	parent_process(int status, t_token **tokens, int *pipe_fd)
{
	char	new_line[8192];
	int		bytes;

	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		free_tokens(*tokens);
		exit(1);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		free_tokens(*tokens);
		(*tokens) = NULL;
	}
	else
	{
		bytes = read(pipe_fd[0], new_line, 8192);
		if (bytes >= 0 && bytes < 8192)
		{
			new_line[bytes] = '\0';
			tokenize(new_line, tokens);
		}
		else
			perror("Erro de leitura ou tamanho excedido.\n");
	}
}

void	handle_pipe_stdin(char *line, t_token **tokens, int *i)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	signal(SIGINT, SIG_IGN);
	add_token(*tokens, "|", 0);
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
		child_process(tokens, pipe_fd);
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
		parent_process(status, tokens, pipe_fd);
	}
}
