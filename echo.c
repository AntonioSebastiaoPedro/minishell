/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:04:34 by ansebast          #+#    #+#             */
/*   Updated: 2024/12/08 08:11:11 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_args(t_command *cmd)
{
	if (cmd->invalid_redir)
	{
		printf("akatsuki: syntax error\n");
		return (2);
	}
	return (0);
}

int	is_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] == 'n')
			i++;
		if (i > 1 && arg[i] == '\0')
			return (0);
	}
	return (1);
}

int	ft_echo(t_command *cmd)
{
	int	newline;
	int	i;

	newline = validate_args(cmd);
	if (newline)
		return (newline);
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i] && !is_option(cmd->args[i]))
		{
			newline = -1;
			i++;
		}
		while (cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			if (cmd->args[i + 1])
				printf(" ");
			i++;
		}
	}
	if (newline != -1)
		printf("\n");
	return (0);
}
