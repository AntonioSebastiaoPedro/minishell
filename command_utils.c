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

int	is_command(const char *token)
{
	return (token != NULL && !ft_isdigit(token[0]) && ft_strcmp(token, "|") != 0
		&& ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0
		&& ft_strcmp(token, ">>") != 0 && ft_strcmp(token, "<<") != 0);
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

void	expand_command_args(t_command *cmd, t_env **env)
{
	int	i;
	int	arg_pos;

	i = 0;
	arg_pos = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			cmd->args[i] = expand_variables(cmd->args[i], cmd, &arg_pos, env);
			i++;
			arg_pos++;
		}
	}
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
