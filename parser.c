/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:03 by ateca             #+#    #+#             */
/*   Updated: 2024/11/27 11:52:13 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_error(t_command *current_cmd, t_token *tokens)
{
	if ((current_cmd == NULL && tokens->next == NULL)
		|| (is_redirection(tokens->value) && tokens->next != NULL
			&& ft_strcmp(tokens->next->value, "|") == 0)
		|| (ft_strcmp(tokens->value, "|") == 0 && tokens->next != NULL
			&& is_redirection(tokens->next->value))
		|| (current_cmd == NULL && ft_strcmp(tokens->value, "|") == 0
			&& tokens->next != NULL && is_command(tokens->next->value, 0))
		|| (current_cmd != NULL && is_redirection(tokens->value)
			&& tokens->next == NULL)
		|| (current_cmd != NULL && is_redirection(tokens->value)
			&& tokens->next != NULL && is_redirection(tokens->next->value))
		|| (is_redirection(tokens->value)
			&& tokens->next != NULL && is_redirection(tokens->next->value)))
	{
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

t_command	*process_current_token(t_token **tks, t_command **commands,
		t_command *cmd, int *skip_file_redirection)
{
	t_token	*tokens;

	tokens = *tks;
	if (cmd == NULL && is_command(tokens->value, tokens->interpret))
		cmd = add_command(commands, ft_strdup(tokens->value));
	else if (check_redir_error(cmd, tokens) && tokens->interpret != 1)
		print_error_redir_single(tokens->value, commands, tks);
	else if (cmd == NULL && is_redirection(tokens->value))
	{
		*skip_file_redirection = 1;
		cmd = add_command(commands, NULL);
		handle_redirection(tokens, cmd);
		cmd = NULL;
	}
	else if (cmd != NULL && ft_strcmp(tokens->value, "|") == 0
		&& tokens->interpret != 1)
		cmd = NULL;
	else if (cmd && is_redirection(tokens->value) && tokens->interpret != 1)
	{
		*skip_file_redirection = 1;
		handle_redirection(tokens, cmd);
	}
	else if (cmd != NULL && is_argument(tokens->value, tokens->interpret))
		add_argument(cmd, tokens);
	return (cmd);
}

int	is_argument(const char *token, int interpret)
{
	return (token != NULL && ((!is_redirection(token)
				&& ft_strcmp(token, "|") != 0) || interpret == 1));
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*commands;
	t_command	*current_cmd;
	int			skip_file_redirection;

	commands = NULL;
	current_cmd = NULL;
	skip_file_redirection = 0;
	while (tokens)
	{
		if (skip_file_redirection)
		{
			skip_file_redirection = 0;
			if (tokens->next != NULL && is_redirection(tokens->next->value))
				current_cmd = NULL;
		}
		else
			current_cmd = process_current_token(&tokens, &commands, current_cmd,
					&skip_file_redirection);
		if (tokens)
			tokens = tokens->next;
	}
	return (commands);
}
