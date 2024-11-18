/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:36:42 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/18 02:17:30 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_variable_name(const char *str, int *i, char *var_name)
{
	int	j;

	j = 0;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
}

void	check_enval(char **env_val, char **result, int *pos)
{
	if (*env_val)
	{
		ft_strcpy(*result + *pos, *env_val);
		*pos += ft_strlen(*env_val);
	}
}

char	*get_env_value(char *var, t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->var, var) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

char	*expand_variables(const char *str, t_command *cmd, int *arg_pos,
		t_env **env)
{
	int		pos;
	int		i;
	char	*env_val;
	char	*result;
	char	var_name[1024];

	if (cmd->interpret[*arg_pos])
		return (ft_strdup((char *)str));
	result = malloc(sizeof(char) * 1024);
	pos = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			extract_variable_name(str, &i, var_name);
			env_val = get_env_value(var_name, env);
			check_enval(&env_val, &result, &pos);
		}
		else
			result[pos++] = str[i++];
	}
	result[pos] = '\0';
	return (result);
}
