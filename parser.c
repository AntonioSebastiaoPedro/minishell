/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:03 by ateca             #+#    #+#             */
/*   Updated: 2024/11/07 23:14:30 by ansebast         ###   ########.fr       */
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
	if (ft_strcmp(token->value, ">") == 0)
		current_cmd->output_redir = token->next->value;
	else if (ft_strcmp(token->value, "<") == 0)
		current_cmd->input_redir = token->next->value;
	else if (ft_strcmp(token->value, ">>") == 0)
	{
		current_cmd->output_redir = token->next->value;
		current_cmd->append = 1;
	}
	else if (ft_strcmp(token->value, "<<") == 0)
		current_cmd->input_redir = token->next->value;
}

int	is_argument(const char *token)
{
	return (token != NULL && !is_redirection(token) \
		&& ft_strcmp(token, "|") != 0);
}

void	add_argument(t_command *cmd, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd->args)
		while (cmd->args[i])
			i++;
	if (cmd->interpret)
		while (cmd->interpret[j])
			j++;
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * (i + 2));
	cmd->args[i] = ft_strdup(token->value);
	cmd->args[i + 1] = NULL;
	cmd->interpret = ft_realloc(cmd->interpret, sizeof(int) * (j + 1));
	cmd->interpret[j] = token->interpret;
}

t_command	*parse_tokens(t_token *tokens)
{
	int			skip_file;
	t_command	*commands;
	t_command	*current_cmd;

	skip_file = 0;
	commands = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (skip_file)
			skip_file = 0;
		else if (is_command(tokens->value) && !current_cmd)
			current_cmd = add_command(&commands, tokens->value);
		else if (ft_strcmp(tokens->value, "|") == 0)
			current_cmd = NULL;
		else if (is_redirection(tokens->value) && current_cmd)
		{
			handle_redirection(tokens, current_cmd);
			skip_file = 1;
		}
		else if (is_argument(tokens->value) && current_cmd)
			add_argument(current_cmd, tokens);
		tokens = tokens->next;
	}
	return (commands);
}
