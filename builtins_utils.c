/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:37:31 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/09 18:30:49 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_status_builtin(int *status, t_command *cmd, t_status_cmd *st)
{
	if (ft_strcmp(cmd->command, "echo") == 0)
		*status = (ft_echo(cmd));
	else if (ft_strcmp(cmd->command, "cd") == 0)
		*status = (ft_cd(cmd->args, st->env));
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		*status = (ft_pwd());
	else if (ft_strcmp(cmd->command, "env") == 0)
		*status = (ft_env(cmd, st->env));
	else if (ft_strcmp(cmd->command, "export") == 0)
		*status = (ft_export(cmd, st->env));
	else if (ft_strcmp(cmd->command, "unset") == 0)
		*status = (ft_unset(cmd, st->env));
	else if (ft_strcmp(cmd->command, "exit") == 0)
		*status = (ft_exit(cmd, st));
}

int	exec_builtin(t_command *cmd, t_status_cmd *st)
{
	int	status;

	status = 0;
	if (cmd->write_pipe_fd != -1)
	{
		dup2(cmd->write_pipe_fd, STDOUT_FILENO);
		close(cmd->write_pipe_fd);
	}
	get_status_builtin(&status, cmd, st);
	if (cmd->write_pipe_fd != -1 && cmd->next && !cmd->next->output_redir)
	{
		dup2(st->original_stdout, STDOUT_FILENO);
		close(st->original_stdout);
	}
	return (status);
}

int	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0);
}
