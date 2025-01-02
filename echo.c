/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:04:34 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/22 00:56:54 by ansebast         ###   ########.fr       */
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

int	is_newline(char *first_arg)
{
	int	i;

	i = 1;
	while (first_arg[i])
	{
		if (first_arg[i] != 'n')
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
		if (cmd->args[0] && cmd->args[0][0] == '-' && is_newline(cmd->args[0]))
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
