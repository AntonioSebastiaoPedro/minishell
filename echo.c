/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:04:34 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/09 07:09:23 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_args(t_command *cmd)
{
	char	*error_message;

	error_message = "minishell: syntax error\n";
	if (cmd->invalid_redir)
	{
		write(2, error_message, ft_strlen(error_message));
		return (2);
	}
	return (0);
}

int	is_newline(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
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
		while (cmd->args[i] && is_newline(cmd->args[i]))
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
	if (newline != -1 || !isatty(STDOUT_FILENO))
		printf("\n");
	return (0);
}
