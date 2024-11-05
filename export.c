/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:17:44 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/05 07:48:32 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **args)
{
	extern char	**environ;
	char		*var;
	char		*value;
	int	i;

	i = 0;
	if (!args || !args[0])
	{
		while (environ[i])
			printf("declare -x %s\n", environ[i++]);
	}
	else
	{
		var = strtok(args[0], "=");
		value = strtok(NULL, "=");
		if (var && value)
			setenv(var, value, 1);
	}
}
