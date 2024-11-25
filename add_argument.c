/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:22:31 by ateca             #+#    #+#             */
/*   Updated: 2024/11/19 15:22:35 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_argument(const char *token)
{
	return (token != NULL && !is_redirection(token)
		&& ft_strcmp(token, "|") != 0);
}

void	add_argument(t_command *cmd, const char *arg)
{
	int	count;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
		{
			count++;
		}
	}
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * (count + 2));
	if (!cmd->args)
	{
		perror("malloc failed");
		return ;
	}
	cmd->args[count] = ft_strdup(arg);
	cmd->args[count + 1] = NULL;
}
