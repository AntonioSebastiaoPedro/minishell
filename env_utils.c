/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:17:28 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/10 14:58:52 by ansebast         ###   ########.fr       */
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

	new_env = ft_newenv(name);
	add_back(envs, new_env);
	update_index(*envs);
	return (new_env);
}

t_env	*last_env(t_env *head)
{
	if (head)
		while (head->next)
			head = head->next;
	return (head);
}

void	add_back(t_env **head, t_env *new_env)
{
	t_env	*last;

	if (head && *head)
	{
		last = last_env(*head);
		last->next = new_env;
		new_env->index = last->index + 1;
		new_env->next = NULL;
	}
	else
		*head = new_env;
}

t_env	*ft_newenv(char *name)
{
	t_env	*new_env;
	char	*var;
	char	*value;
	char	*name_copy;
	int		show;

	new_env = malloc(sizeof(t_env));
	name_copy = ft_strdup(name);
	show = 0;
	if (ft_strchr(name_copy, '='))
		show = 1;
	var = strtok(name_copy, "=");
	value = strtok(NULL, "=");
	new_env->var = var;
	new_env->value = value;
	if (!var)
		new_env->var = ft_strdup("");
	if (!value)
		new_env->value = ft_strdup("");
	new_env->index = 0;
	new_env->show = show;
	new_env->next = NULL;
	return (new_env);
}
