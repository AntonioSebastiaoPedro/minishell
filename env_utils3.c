/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:45:25 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/18 01:45:46 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_env **env)
{
	t_env	*current;
	int		shlvl_value;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->var, "SHLVL") == 0)
		{
			shlvl_value = ft_atoi(current->value);
			shlvl_value++;
			free(current->value);
			current->value = ft_strdup(ft_itoa(shlvl_value));
			return ;
		}
		current = current->next;
	}
	add_env(env, "SHLVL=1");
}