/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:41:38 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/07 23:13:53 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_command *cmd, t_env *env)
{
	int	i;

	while (cmd)
	{
		i = -1;
		if (cmd->args)
			while (cmd->args[++i])
				cmd->args[i] = expand_variables(cmd->args[i], cmd, &i);
		if (is_builtin(cmd->command))
			exec_builtin(cmd, env);
		else
			printf("The cmd is not a built-in\n");
		cmd = cmd->next;
	}
}

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
