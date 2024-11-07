/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:37:31 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/07 20:44:19 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_command *cmd, t_env *env)
{
	if (ft_strcmp(cmd->command, "echo") == 0)
		ft_echo(cmd->args);
	else if (ft_strcmp(cmd->command, "cd") == 0)
		ft_cd(cmd->args);
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->command, "env") == 0)
		ft_env(cmd, env);
	else if (ft_strcmp(cmd->command, "export") == 0)
		ft_export(cmd, env);
	else if (ft_strcmp(cmd->command, "exit") == 0)
		exit(0);
}

int	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0);
}
