/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:17:28 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/08 11:35:53 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_index(t_env *head)
{
	int		index;
	t_env	*current;

	index = 0;
	current = head;
	while (current != NULL)
	{
		current->index = index;
		index++;
		current = current->next;
	}
}

t_env	*add_env(t_env **envs, char *name)
{
	t_env	*new_env;
	char	*var;
	char	*value;
	char	*name_copy;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		perror("malloc");
		return (NULL);
	}
	name_copy = strdup(name);
	var = strtok(name_copy, "=");
	value = strtok(NULL, "=");
	new_env->var = var;
	new_env->value = value;
	if (!var)
		new_env->var = ft_strdup("");
	if (!value)
		new_env->value = ft_strdup("");
	new_env->next = *envs;
	*envs = new_env;
	update_index(*envs);
	return (new_env);
}

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
