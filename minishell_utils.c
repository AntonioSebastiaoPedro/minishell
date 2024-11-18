/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:34:13 by ateca             #+#    #+#             */
/*   Updated: 2024/11/18 16:34:15 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->command, "echo") == 0)
		ft_echo(cmd->args);
	else if (ft_strcmp(cmd->command, "cd") == 0)
		ft_cd(cmd->args);
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->command, "exit") == 0)
		exit(0);
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0);
}

int	handle_redirections(t_command **cmd)
{
	if ((*cmd)->input_redir != NULL)
		return (handle_input_redirection(*cmd));
	else if ((*cmd)->output_redir != NULL)
		return (handle_output_redirection(cmd));
	return (0);
}
