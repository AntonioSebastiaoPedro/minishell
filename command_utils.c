/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:38 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/27 11:54:53 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(const char *token, int interpret)
{
	return (token && ((!ft_isdigit(token[0]) && ft_strcmp(token, "|") != 0
				&& ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0
				&& ft_strcmp(token, ">>") != 0 && ft_strcmp(token, "<<") != 0)
			|| interpret == 2));
}

void	atribute_cmd_values(t_command **cmd)
{
	(*cmd)->args = NULL;
	(*cmd)->input_redir = NULL;
	(*cmd)->output_redir = NULL;
	(*cmd)->append = 0;
	(*cmd)->heredoc = 0;
	(*cmd)->write_pipe_fd = -1;
	(*cmd)->read_pipe_fd = -1;
	(*cmd)->interpret = NULL;
	(*cmd)->invalid_redir = 0;
	(*cmd)->next = NULL;
}

t_command	*add_command(t_command **commands, char *command)
{
	t_command	*new_command;
	t_command	*current;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
	{
		perror("minishell: malloc failed");
		return (NULL);
	}
	new_command->command = command;
	atribute_cmd_values(&new_command);
	if (*commands == NULL)
		*commands = new_command;
	else
	{
		current = *commands;
		while (current->next != NULL)
			current = current->next;
		current->next = new_command;
	}
	return (new_command);
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
	cmd->args[i] = ft_strdup(token->value);
	cmd->args[i + 1] = NULL;
	current_size_i = i + 2;
	cmd->interpret = ft_realloc(cmd->interpret, sizeof(int) * current_size_j,
			sizeof(int) * (j + 1));
	cmd->interpret[j] = token->interpret;
	current_size_j = i + 1;
}

void	free_commands(t_command *commands)
{
	int			i;
	t_command	*next;

	while (commands != NULL)
	{
		next = commands->next;
		if (commands->command)
			free(commands->command);
		if (commands->args)
		{
			i = -1;
			while (commands->args[++i] != NULL)
			{
				free(commands->args[i]);
				commands->args[i] = NULL;
			}
			free(commands->args);
			commands->args = NULL;
		}
		if (commands->interpret)
			free(commands->interpret);
		free(commands);
		commands = next;
	}
}
