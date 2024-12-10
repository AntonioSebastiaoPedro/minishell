/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:28:48 by ateca             #+#    #+#             */
/*   Updated: 2024/12/07 17:47:03 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(const char *token)
{
	return (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}

void	handle_redirection(t_token *token, t_command *current_cmd)
{
	if (ft_strcmp(token->value, ">") == 0 && token->next != NULL)
		current_cmd->output_redir = token->next->value;
	else if (ft_strcmp(token->value, "<") == 0 && token->next != NULL)
		current_cmd->input_redir = token->next->value;
	else if (ft_strcmp(token->value, ">>") == 0 && token->next != NULL)
	{
		current_cmd->output_redir = token->next->value;
		current_cmd->append = 1;
	}
	else if (ft_strcmp(token->value, "<<") == 0 && token->next != NULL)
	{
		current_cmd->input_redir = token->next->value;
		current_cmd->heredoc = 1;
	}
}

int	handle_redirections(t_command **cmd, t_status_cmd st, pid_t *pids, int *i)
{
	int	result;

	result = 0;
	if ((*cmd)->input_redir != NULL)
	{
		result = handle_input_redirection(*cmd, st.original_stdout, &st.status);
		if (result == -3)
		{
			*cmd = (*cmd)->next;
			pids[(*i)] = -1;
			(*i)++;
		}
	}
	else if ((*cmd)->output_redir != NULL)
		return (handle_output_redirection(cmd));
	return (result);
}

void	print_error_redir_single(char *token, t_command **cmds, t_token **tks)
{
	char	*program_name;
	char	*error_message;

	program_name = "minishell: ";
	error_message = "syntax error near unexpected token\n";
	if ((*tks) && (*tks)->next && is_redirection(token)
		&& ft_strcmp((*tks)->next->value, "|") == 0)
		error_message = "syntax error near unexpected token `|'\n";
	else if (is_redirection(token))
	{
		token = ft_strjoin("`newline'", "\n");
		if ((*tks) && (*tks)->next != NULL && is_redirection((*tks)->next->value))
		{
			token = ft_strjoin("`", (*tks)->next->value);
			token = ft_strjoin(token, "'\n");
		}
		error_message = "syntax error near unexpected token ";
	}
	else if (ft_strcmp(token, "|") == 0)
		error_message = "syntax error near unexpected token `|'\n";
	write(2, program_name, ft_strlen(program_name));
	write(2, error_message, ft_strlen(error_message));
	write(2, token, ft_strlen(token));
	(*cmds) = NULL;
	(*tks)->next = NULL;
}

void	print_error_no_such_file_or_directory(char *file_redir)
{
	char	*program_name;
	char	*colon_space;
	char	*newline;
	char	*error_message;

	program_name = "minishell: ";
	colon_space = ": ";
	newline = "\n";
	error_message = strerror(errno);
	write(2, program_name, ft_strlen(program_name));
	write(2, file_redir, ft_strlen(file_redir));
	write(2, colon_space, ft_strlen(colon_space));
	write(2, error_message, ft_strlen(error_message));
	write(2, newline, ft_strlen(newline));
}
