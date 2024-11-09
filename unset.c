/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:29:39 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/09 18:48:22 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_remove_if(t_env **envs, char *var, int (*cmp)())
{
	t_env	*remove;
	t_env	*current;

	current = *envs;
	while (current && current->next)
	{
		if ((*cmp)(current->next->var, var) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			free(remove);
			break;
		}
		current = current->next;
	}
}

void	ft_unset(t_command *cmd, t_env **env)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
		ft_env_remove_if(env, cmd->args[i], ft_strcmp);
}
