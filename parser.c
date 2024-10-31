/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:03 by ateca             #+#    #+#             */
/*   Updated: 2024/10/30 16:54:05 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(const char *token)
{
	return (token != NULL && !isdigit(token[0]) && strcmp(token, "|") != 0
		&& strcmp(token, "<") != 0 && strcmp(token, ">") != 0
		&& strcmp(token, ">>") != 0 && strcmp(token, "<<") != 0);
}

t_command	*add_command(t_command **commands, const char *command)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
	{
		perror("malloc");
		return (NULL);
	}
	new_command->command = strdup(command);
	new_command->args = NULL;
	new_command->input_redir = NULL;
	new_command->output_redir = NULL;
	new_command->append = 0;
	new_command->next = *commands;
	*commands = new_command;
	return (new_command);
}

int	is_redirection(const char *token)
{
	return (strcmp(token, ">") == 0 || strcmp(token, "<") == 0
		|| strcmp(token, ">>") == 0 || strcmp(token, "<<") == 0);
}

void	handle_redirection(t_token *token, t_command *current_cmd)
{
	if (strcmp(token->value, ">") == 0)
		current_cmd->output_redir = token->next->value;
	else if (strcmp(token->value, "<") == 0)
		current_cmd->input_redir = token->next->value;
	else if (strcmp(token->value, ">>") == 0)
	{
		current_cmd->output_redir = token->next->value;
		current_cmd->append = 1;
	}
	else if (strcmp(token->value, "<<") == 0)
		current_cmd->input_redir = token->next->value;
}

int	is_argument(const char *token)
{
	return (token != NULL && !is_redirection(token) && strcmp(token, "|") != 0);
}

void	add_argument(t_command *cmd, const char *arg)
{
	int	count;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
		{
			count++;
		}
	}
	cmd->args = realloc(cmd->args, sizeof(char *) * (count + 2));
	cmd->args[count] = strdup(arg);
	cmd->args[count + 1] = NULL;
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*commands;
	t_command	*current_cmd;

	commands = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (is_command(tokens->value) && !current_cmd)
			current_cmd = add_command(&commands, tokens->value);
		else if (strcmp(tokens->value, "|") == 0)
			current_cmd = NULL;
		else if (is_redirection(tokens->value) && current_cmd)
			handle_redirection(tokens, current_cmd);
		else if (is_argument(tokens->value) && current_cmd)
			add_argument(current_cmd, tokens->value);
		tokens = tokens->next;
	}
	return (commands);
}
