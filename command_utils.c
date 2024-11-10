/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:38 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/10 14:34:42 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(const char *token)
{
	return (token != NULL && !ft_isdigit(token[0]) && ft_strcmp(token, "|") != 0
		&& ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0
		&& ft_strcmp(token, ">>") != 0 && ft_strcmp(token, "<<") != 0);
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
	new_command->command = ft_strdup(command);
	new_command->args = NULL;
	new_command->interpret = NULL;
	new_command->input_redir = NULL;
	new_command->output_redir = NULL;
	new_command->append = 0;
	new_command->next = *commands;
	*commands = new_command;
	return (new_command);
}

void	free_commands(t_command *commands)
{
	int			i;
	t_command	*current;
	t_command	*next;

	if (commands == NULL)
		return ;
	current = commands;
	while (current)
	{
		next = current->next;
		free(current->command);
		if (current->args)
		{
			i = -1;
			while (current->args[++i] != NULL)
				free(current->args[i]);
			free(current->args);
		}
		free(current);
		current = next;
	}
}
