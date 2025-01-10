/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:15:57 by ateca             #+#    #+#             */
/*   Updated: 2024/11/25 20:16:10 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expects_stdin(char *cmd)
{
	int		i;
	char	*commands[10];

	i = 0;
	commands[0] = "grep";
	commands[1] = "awk";
	commands[2] = "sed";
	commands[3] = "cat";
	commands[4] = "wc";
	commands[5] = "sort";
	commands[6] = "uniq";
	commands[7] = "cut";
	commands[8] = "tr";
	commands[9] = NULL;
	while (commands[i] != NULL)
	{
		if (ft_strcmp(cmd, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	restore_stdio(int original_stdin, int original_stdout, int status)
{
	g_exit_status = status;
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

void	free_arguments(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

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
