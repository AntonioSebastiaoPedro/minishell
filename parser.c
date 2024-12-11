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
			&& tokens->next != NULL && is_command(tokens->next->value))
		|| (current_cmd != NULL && is_redirection(tokens->value)
			&& tokens->next == NULL)
		|| (current_cmd != NULL && is_redirection(tokens->value)
			&& tokens->next != NULL && is_redirection(tokens->next->value))
		|| (is_redirection(tokens->value)
			&& tokens->next != NULL && is_redirection(tokens->next->value)))
	{
		return (1);
	}
	return (0);
}

t_command	*process_current_token(t_token **tks, t_command **commands,
		t_command *current_cmd, int *skip_file_redirection)
{
	t_token	*tokens;

	tokens = *tks;
	if (current_cmd == NULL && is_command(tokens->value))
		current_cmd = add_command(commands, ft_strdup(tokens->value));
	else if (check_redir_error(current_cmd, tokens))
		print_error_redir_single(tokens->value, commands, tks);
	else if (current_cmd == NULL && is_redirection(tokens->value))
	{
		*skip_file_redirection = 1;
		current_cmd = add_command(commands, NULL);
		handle_redirection(tokens, current_cmd);
		current_cmd = NULL;
	}
	else if (current_cmd != NULL && ft_strcmp(tokens->value, "|") == 0)
		current_cmd = NULL;
	else if (current_cmd != NULL && is_redirection(tokens->value))
	{
		*skip_file_redirection = 1;
		handle_redirection(tokens, current_cmd);
	}
	else if (current_cmd != NULL && is_argument(tokens->value))
		add_argument(current_cmd, tokens);
	return (current_cmd);
}

int	is_argument(const char *token)
{
	return (token != NULL && !is_redirection(token)
		&& ft_strcmp(token, "|") != 0);
}

void	add_argument(t_command *cmd, t_token *token)
{
	int			i;
	int			j;
	static int	current_size_i;
	static int	current_size_j;

	i = 0;
	j = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			i++;
		j = i;
	}
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * current_size_i,
			sizeof(char *) * (i + 2));
	cmd->args[i] = token->value;
	cmd->args[i + 1] = NULL;
	current_size_i = i + 2;
	cmd->interpret = ft_realloc(cmd->interpret, sizeof(int) * current_size_j,
			sizeof(int) * (j + 1));
	cmd->interpret[j] = token->interpret;
	current_size_j = i + 1;
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
		tokens = tokens->next;
	}
	return (commands);
}
