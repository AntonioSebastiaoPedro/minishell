/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:00:41 by ansebast          #+#    #+#             */
/*   Updated: 2024/12/07 17:04:29 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_command *cmd)
{
	printf("exit\n");
	if (!cmd->args)
		exit(0);
	if (!ft_isint(cmd->args[0]))
	{
		printf("minishell: exit: %s: requires a numeric argument\n",
			cmd->args[0]);
		exit(2);
	}
	if (cmd->args[1])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	//free_tokens(tokens);
	free_commands(cmd);
	exit(ft_atoi(cmd->args[0]));
}
