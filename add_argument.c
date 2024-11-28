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

void	add_argument(t_command *cmd, char *arg)
{
	int			count;
	static int	current_size;

	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	else
		current_size = 0;
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * current_size,
			sizeof(char *) * (count + 2));
	if (!cmd->args)
	{
		perror("malloc failed");
		return ;
	}
	cmd->args[count] = arg;
	cmd->args[count + 1] = NULL;
	current_size = count + 2;
}
