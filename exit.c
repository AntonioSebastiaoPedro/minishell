/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:00:41 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/09 18:37:12 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_command *cmd, t_status_cmd *st)
{
	printf("exit\n");
	if (!cmd->args)
		exit_free_resources(g_exit_status, cmd, st);
	if (!ft_islong(cmd->args[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[0]);
		exit_free_resources(22, cmd, st);
	}
	if (cmd->args[1])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit_free_resources(ft_atoi(cmd->args[0]), cmd, st);
	return (0);
}

void	exit_free_resources(int status_exit, t_command *cmd, t_status_cmd *st)
{
	free_commands(cmd);
	free_tokens(*st->tokens);
	free(st->pids);
	free_env(st->env);
	exit(status_exit);
}
