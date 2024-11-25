/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:42:21 by ateca             #+#    #+#             */
/*   Updated: 2024/11/19 15:42:22 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(char *token)
{
	return (token != NULL && !ft_isdigit(token[0]) && ft_strcmp(token, "|") != 0
		&& ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0
		&& ft_strcmp(token, ">>") != 0 && ft_strcmp(token, "<<") != 0);
}

t_command	*add_command(t_command **commands, char *command)
{
	t_command	*new_command;
	t_command	*current;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
	{
		perror("malloc failed");
		return (NULL);
	}
	new_command->command = command;
	new_command->args = NULL;
	new_command->input_redir = NULL;
	new_command->output_redir = NULL;
	new_command->append = 0;
	new_command->heredoc = 0;
	new_command->write_pipe_fd = -1;
	new_command->read_pipe_fd = -1;
	new_command->next = NULL;
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
