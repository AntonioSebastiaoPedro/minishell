/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:37:31 by ansebast          #+#    #+#             */
/*   Updated: 2024/12/08 08:20:00 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_status_builtin(int *status, t_command *cmd, t_env **env)
{
	if (ft_strcmp(cmd->command, "echo") == 0)
		*status = (ft_echo(cmd));
	else if (ft_strcmp(cmd->command, "cd") == 0)
		*status = (ft_cd(cmd->args, env));
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		*status = (ft_pwd());
	else if (ft_strcmp(cmd->command, "env") == 0)
		*status = (ft_env(cmd, env));
	else if (ft_strcmp(cmd->command, "export") == 0)
		*status = (ft_export(cmd, env));
	else if (ft_strcmp(cmd->command, "unset") == 0)
		*status = (ft_unset(cmd, env));
	else if (ft_strcmp(cmd->command, "exit") == 0)
		*status = (ft_exit(cmd));
}

int	exec_builtin(t_command *cmd, int original_stdout, t_env **env)
{
	int	status;

	status = 0;
	if (cmd->write_pipe_fd != -1)
	{
		dup2(cmd->write_pipe_fd, STDOUT_FILENO);
		close(cmd->write_pipe_fd);
	}
	get_status_builtin(&status, cmd, env);
	if (cmd->write_pipe_fd != -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
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
