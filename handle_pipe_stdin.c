/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_stdin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:21:15 by ateca             #+#    #+#             */
/*   Updated: 2024/11/23 12:21:19 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process_pipe_heredoc(char *line, t_token **tokens)
{
	char	*new_line;
	char	*next_line;

	signal(SIGINT, handle_sigint_heredoc);
	*tokens = add_token(*tokens, "|");
	next_line = readline("> ");
	if (next_line == NULL)
	{
		free(line);
		write(2, "minishell: ", 11);
		write(2, "syntax error: unexpected end of file\n", 37);
		write(2, "exit\n", 5);
		exit(1);
	}
	new_line = ft_strdup(next_line);
	free(next_line);
	tokenize(new_line, tokens);
	free(new_line);
	exit(0);
}

void	handle_pipe_stdin(char *line, t_token **tokens, int *i)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_process_pipe_heredoc(line, tokens);
	else if (pid < 0)
	{
		perror("minishell: fork failed");
	}
	else
	{
		waitpid(pid, &status, 0);
		*i = ft_strlen(line);
		signal(SIGINT, handle_sigint);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			rl_clear_history();
			free_tokens(*tokens);
			exit(1);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			*tokens = NULL;
	}
}
