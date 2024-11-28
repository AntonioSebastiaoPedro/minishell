/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:15:57 by ateca             #+#    #+#             */
/*   Updated: 2024/11/25 20:16:10 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expects_stdin(char *cmd)
{
	int		i;
	char	*commands[10];

	i = 0;
	commands[0] = "grep";
	commands[1] = "awk";
	commands[2] = "sed";
	commands[3] = "cat";
	commands[4] = "wc";
	commands[5] = "sort";
	commands[6] = "uniq";
	commands[7] = "cut";
	commands[8] = "tr";
	commands[9] = NULL;
	while (commands[i] != NULL)
	{
		if (ft_strcmp(cmd, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
