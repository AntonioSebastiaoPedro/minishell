/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:19:57 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/07 20:42:49 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_index_list(t_env *tab)
{
	char	*var_temp;
	char	*value_temp;
	int		index_temp;
	t_env	*current;

	current = tab;
	while (current && current->next)
	{
		if (current->index > current->next->index)
		{
			value_temp = current->value;
			var_temp = current->var;
			index_temp = current->index;
			current->var = current->next->var;
			current->next->var = var_temp;
			current->value = current->next->value;
			current->next->value = value_temp;
			current->index = current->next->index;
			current->next->index = index_temp;
			current = tab;
		}
		else
			current = current->next;
	}
}

int	ft_env(t_command *cmd, t_env *env)
{
	t_env	*temp;

	if (cmd->args)
	{
		ft_putstr_fd("env: No options or arguments should be passed\n", 2);
		return (1);
	}
	temp = env;
	sort_index_list(temp);
	while (temp)
	{
		printf("%s=%s\n", temp->var, temp->value);
		temp = temp->next;
	}
	return (0);
}
