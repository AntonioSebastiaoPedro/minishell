/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:28:48 by ateca             #+#    #+#             */
/*   Updated: 2024/11/28 15:16:33 by ansebast         ###   ########.fr       */
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

int	handle_redirections(t_command **cmd, int fd_stdout)
{
	if ((*cmd)->input_redir != NULL)
		return (handle_input_redirection(*cmd, fd_stdout));
	else if ((*cmd)->output_redir != NULL)
		return (handle_output_redirection(cmd));
	return (0);
}

void	print_error_redirection_single(char *redir)
{
	char	*program_name;
	char	*error_message;
	char	*newline;

	newline = "\n";
	program_name = "minishell: ";
	write(2, program_name, ft_strlen(program_name));
	if (ft_strcmp(redir, ">") == 0 || ft_strcmp(redir, "<") == 0
		|| ft_strcmp(redir, ">>") == 0 || ft_strcmp(redir, "<<") == 0)
	{
		error_message = "syntax error near unexpected token `newline'";
	}
	else if (ft_strcmp(redir, "|") == 0)
	{
		error_message = "syntax error near unexpected token `|'";
	}
	write(2, error_message, ft_strlen(error_message));
	write(2, newline, ft_strlen(newline));
}

void	print_error_redirection_file(char *file_redir)
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
