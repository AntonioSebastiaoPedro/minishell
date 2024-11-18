/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:17:44 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/18 11:58:08 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_str_list(t_env *tab)
{
	char	*var_temp;
	char	*value_temp;
	int		index_temp;
	t_env	*current;

	current = tab;
	while (current && current->next)
	{
		if (ft_strcmp(current->var, current->next->var) > 0)
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

void	update_env(t_env **env, char *name)
{
	char	*var;
	char	*value;
	char	*name_copy;
	int		show;

	name_copy = ft_strdup(name);
	show = 0;
	if (ft_strchr(name_copy, '='))
		show = 1;
	var = ft_strtok_2(name_copy, "=");
	value = ft_strtok_2(NULL, "=");
	(*env)->var = var;
	(*env)->value = value;
	if (!var)
		(*env)->var = ft_strdup("");
	if (!value)
		(*env)->value = ft_strdup("");
	(*env)->index = 0;
	(*env)->show = show;
	(*env)->next = NULL;
}

t_env	*get_env(char *var, t_env **env, int (*cmp)())
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (cmp(temp->var, var) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	add_args_env(char **args, t_env **env)
{
	int		i;
	int		status;
	char	var[70000];
	t_env	*new_env;

	status = 0;
	i = -1;
	while (args[++i])
	{
		if (!ft_isword(args[i]))
		{
			printf("minishell: export: Invalid identifier %s\n",
				ft_strtok_2(args[i], "="));
			status = 1;
			continue ;
		}
		ft_strcpy(var, args[i]);
		ft_strtok_2(var, "=");
		new_env = get_env(var, env, ft_strcmp);
		if (new_env)
			update_env(&new_env, args[i]);
		else
			add_env(env, args[i]);
	}
	return (status);
}

int	ft_export(t_command *cmd, t_env **env)
{
	t_env	*env_dup;
	int		status;

	env_dup = *env;
	if (!cmd->args)
	{
		sort_str_list(env_dup);
		while (env_dup)
		{
			printf("declare -x %s=", env_dup->var);
			printf("%c%s%c\n", '\"', env_dup->value, '\"');
			env_dup = env_dup->next;
		}
		status = 0;
	}
	else
		status = (add_args_env(cmd->args, env));
	return (status);
}
