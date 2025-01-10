/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:34:35 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/10 19:16:12 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_check_cmd(char *exec_path, t_command **cmd, t_status_cmd *st)
{
	char	*msg;

	if (!exec_path)
	{
		msg = ": command not found";
		write(2, (*cmd)->command, ft_strlen((*cmd)->command));
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
		exit_free_resources(127, st);
	}
}

void	print_error_unclosed_quote(char *buffer, char quote, const char *line,
		int *i)
{
	char	*message_error;

	g_exit_status = 1;
	(*i) = ft_strlen(line);
	message_error = "minishell: syntax error: unclosed quote ";
	write(2, message_error, ft_strlen(message_error));
	write(2, &quote, 1);
	write(2, "\n", 1);
	free(buffer);
	buffer = NULL;
}

void	print_error_redir_single(char *token, t_command **cmds, t_token **tks)
{
	char	*error_message;

	error_message = "minishell: syntax error near unexpected token";
	if (((*tks) && (*tks)->next && is_redirection(token)
			&& ft_strcmp((*tks)->next->value, "|") == 0)
		|| ft_strcmp(token, "|") == 0)
	{
		token = NULL;
		error_message = "minishell: syntax error near unexpected token `|'\n";
	}
	else if (is_redirection(token))
	{
		token = ft_strjoin("`newline'", "\n");
		error_message = "minishell: syntax error near unexpected token ";
	}
	write(2, error_message, ft_strlen(error_message));
	write(2, token, ft_strlen(token));
	free(token);
	free_commands((*cmds));
	(*cmds) = NULL;
	(*tks) = NULL;
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

void	print_invalid_identifier_error(char *arg)
{
	char	*error_msg_prefix;
	char	error_msg[70000];

	error_msg[0] = '\0';
	error_msg_prefix = "minishell: export: `";
	ft_strlcat(error_msg, error_msg_prefix, sizeof(error_msg));
	ft_strlcat(error_msg, arg, sizeof(error_msg));
	ft_strlcat(error_msg, "': ", sizeof(error_msg));
	ft_strlcat(error_msg, "not a valid identifier", sizeof(error_msg));
	ft_strlcat(error_msg, "\n", sizeof(error_msg));
	write(2, error_msg, ft_strlen(error_msg));
}
