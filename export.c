/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:17:44 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/07 19:11:30 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_str_list(t_env *tab, int (*cmp)(const char *str1,
			const char *str2))
{
	char	*var_temp;
	char	*value_temp;
	int		index_temp;
	t_env	*current;

	current = tab;
	while (current && current->next)
	{
		if ((*cmp)(current->var, current->next->var) > 0)
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

void	ft_export(t_command *cmd, t_env *env)
{
	t_env	*env_dup;

	env_dup = env;
	if (!cmd->args || !cmd->args[0])
	{
		sort_str_list(env_dup, ft_strcmp);
		while (env_dup)
		{
			printf("declare -x %s=", env_dup->var);
			printf("%c%s%c\n", '\"', env_dup->value, '\"');
			env_dup = env_dup->next;
		}
	}
}
