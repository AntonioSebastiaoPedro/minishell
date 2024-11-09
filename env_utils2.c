/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:53:51 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/09 18:57:51 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next_node;

	current = *env;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->var);
		if (current->value)
			free(current->value);
		free(current);
		current = next_node;
	}
	*env = NULL;
}

void	envcpy(t_env **env_dup, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		add_env(env_dup, src[i]);
		i++;
	}
}
