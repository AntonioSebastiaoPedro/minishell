/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:53:51 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/22 17:00:35 by ansebast         ###   ########.fr       */
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

static int	count_visible_vars(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		if (env_list->show == 1)
			count++;
		env_list = env_list->next;
	}
	return (count);
}

int	init_env_var(char **env_array, int *i, int len)
{
	env_array[*i] = malloc(len * sizeof(char));
	if (!env_array[*i])
	{
		while (*i > 0)
			free(env_array[--*i]);
		free(env_array);
		return (1);
	}
	return (0);
}

char	**env_list_to_array(t_env *env_list)
{
	int		i;
	int		len;
	int		visible_count;
	char	**env_array;

	visible_count = count_visible_vars(env_list);
	env_array = malloc((visible_count + 1) * sizeof(char *));
	i = 0;
	if (!env_array)
		return (NULL);
	while (env_list)
	{
		if (env_list->show == 1)
		{
			len = ft_strlen(env_list->var) + ft_strlen(env_list->value) + 2;
			if (init_env_var(env_array, &i, len))
				return (NULL);
			env_array[i] = ft_strjoin_delimiter(env_list->var, '=',
					env_list->value);
			i++;
		}
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
