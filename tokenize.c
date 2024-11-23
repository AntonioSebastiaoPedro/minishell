/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:56 by ateca             #+#    #+#             */
/*   Updated: 2024/11/05 00:00:03 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection_and_pipes(char *line, int *i, t_token **tokens)
{
	char	operator[2];

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*tokens) = add_token(*tokens, ">>");
		*i += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*tokens) = add_token(*tokens, "<<");
		*i += 2;
	}
	else
	{
		operator[0] = line[*i];
		operator[1] = '\0';
		(*tokens) = add_token(*tokens, operator);
		(*i)++;
	}
}

void	handle_quotes(const char *line, int *i, t_token **tokens)
{
	int		j;
	char	quote;
	char	buffer[256];

	j = 0;
	quote = line[(*i)++];
	while (line[*i] && line[*i] != quote)
	{
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
	(*i)++;
}

void	handle_environment_variable(const char *line, int *i, t_token **tokens)
{
	char	buffer[256];
	int		j;

	j = 0;
	buffer[j++] = line[(*i)++];
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
}

void	handle_word(const char *line, int *i, t_token **tokens)
{
	char	buffer[256];
	int		j;

	j = 0;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && line[*i]
		!= '>' && line[*i] != '<')
	{
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
}

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

void	tokenize(char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '|' && line[i + 1] == '\0')
			handle_pipe_stdin(line, tokens, &i);
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			handle_redirection_and_pipes(line, &i, tokens);
		else if (line[i] == '"' || line[i] == '\'')
			handle_quotes(line, &i, tokens);
		else if (line[i] == '$')
			handle_environment_variable(line, &i, tokens);
		else if (line[i])
			handle_word(line, &i, tokens);
	}
}
