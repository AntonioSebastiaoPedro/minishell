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

int	is_command_pipe(char *line, int i, t_token *tokens)
{
	t_token	*last_token;

	last_token = ft_lstlast_token(tokens);
	if (last_token && line[i] == '|' && check_isspace(line, i))
	{
		if (ft_strcmp(last_token->value, "|") != 0
			&& !is_redirection(last_token->value))
			return (1);
	}
	return (0);
}

void	child_process(t_token **tokens, int *pipe_fd)
{
	char	*next_line;

	signal(SIGINT, handle_sigint_heredoc);
	*tokens = add_token(*tokens, "|", 0);
	while (1)
	{
		next_line = readline("> ");
		if (check_isspace(next_line, -1))
			continue ;
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
}

void	parent_process(int status, t_token **tokens, int *pipe_fd, t_env **env)
{
	char	new_line[2097152];
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
		bytes = read(pipe_fd[0], new_line, 2097152);
		if (bytes >= 0 && bytes < 2097152)
		{
			new_line[bytes] = '\0';
			tokenize(new_line, tokens, env, 0);
		}
		else
			perror("Read error or size exceeded");
	}
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
		parent_process(status, tokens, pipe_fd, env);
	}
}
