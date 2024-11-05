/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:04:34 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/05 01:34:43 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	i = 0;
	if (args)
	{
		if (args[0] && ft_strcmp(args[0], "-n") == 0)
		{
			newline = 0;
			i++;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
	if (newline)
		printf("\n");
}
