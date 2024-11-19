/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:03 by ateca             #+#    #+#             */
/*   Updated: 2024/11/05 00:46:06 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*process_current_token(t_token *tokens, t_command **commands,
		t_command *current_cmd, int *skip_file_redirection)
{
	if (current_cmd == NULL && is_command(tokens->value))
		current_cmd = add_command(commands, ft_strdup(tokens->value));
	else if (current_cmd == NULL && tokens->next == NULL)
	{
		case_redirection_print_message_error(tokens->value);
	}
	else if (current_cmd == NULL && is_redirection(tokens->value))
	{
		*skip_file_redirection = 1;
		current_cmd = add_command(commands, NULL);
		handle_redirection(tokens, current_cmd);
	}
	else if (current_cmd != NULL && ft_strcmp(tokens->value, "|") == 0)
	{
		current_cmd = NULL;
	}
	else if (current_cmd != NULL && is_redirection(tokens->value))
	{
		*skip_file_redirection = 1;
		handle_redirection(tokens, current_cmd);
	}
	else if (current_cmd != NULL && is_argument(tokens->value))
		add_argument(current_cmd, tokens->value);
	return (current_cmd);
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
			current_cmd = process_current_token(tokens, &commands, current_cmd,
					&skip_file_redirection);
		tokens = tokens->next;
	}
	return (commands);
}
