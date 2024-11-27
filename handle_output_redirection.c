/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:43:04 by ateca             #+#    #+#             */
/*   Updated: 2024/11/18 14:43:07 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_arguments(char **args, t_command *next_cmd)
{
	int	i;
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	next_cmd->args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!next_cmd->args)
	{
		perror("malloc failed");
		return (-2);
	}
	i = 0;
	while (i < count)
	{
		next_cmd->args[i] = ft_strdup(args[i]);
		i++;
	}
	next_cmd->args[count] = NULL;
	return (0);
}

int	handle_chained_redirection(t_command **cmd)
{
	if ((*cmd)->command != NULL && ft_strcmp((*cmd)->command, "echo") == 0)
	{
		(*cmd)->next->command = ft_strdup((*cmd)->command);
		if (copy_arguments((*cmd)->args, (*cmd)->next) == -2)
			return (-2);
	}
	else if ((*cmd)->command != NULL)
	{
		(*cmd)->next->command = ft_strdup((*cmd)->command);
		if ((*cmd)->read_pipe_fd != -1 && (*cmd)->heredoc == 1)
		{
			(*cmd)->next->heredoc = 1;
			(*cmd)->next->read_pipe_fd = (*cmd)->read_pipe_fd;
		}
		else
		{
			if ((*cmd)->next->next != NULL)
				(*cmd)->next->next->read_pipe_fd
					= (*cmd)->next->read_pipe_fd;
		}
	}
	*cmd = (*cmd)->next;
	return (0);
}

int	prepare_flags(int append)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append == 1)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

int	process_output_redirection(t_command **cmd, t_command **command)
{
	int	flags;
	int	fd_write;

	flags = prepare_flags((*cmd)->append);
	fd_write = open((*cmd)->output_redir, flags, 0644);
	if (fd_write < 0)
	{
		print_error_redirection_file((*cmd)->output_redir);
		return (-3);
	}
	if ((*cmd)->next && (*cmd)->next->output_redir)
	{
		close(fd_write);
		return (handle_chained_redirection(cmd));
	}
	else
	{
		dup2(fd_write, STDOUT_FILENO);
		close(fd_write);
		*command = *cmd;
		return (1);
	}
}

int	handle_output_redirection(t_command **command)
{
	int			status;
	t_command	*cmd;

	status = 0;
	cmd = *command;
	if (cmd->write_pipe_fd != -1)
		close(cmd->write_pipe_fd);
	while (cmd && cmd->output_redir)
	{
		status = process_output_redirection(&cmd, command);
		if (status != 0)
			break ;
	}
	return (status);
}
