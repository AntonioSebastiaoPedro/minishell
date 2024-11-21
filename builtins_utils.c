/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:37:31 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/22 00:29:06 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_command *cmd, t_env **env, int *status)
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
	return (*status);
}

int	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0);
}
