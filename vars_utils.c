/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:36:42 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/07 19:47:11 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_variable_name(const char *str, int *i, char *var_name)
{
	int	j;

	j = 0;
	(*i)++;
	while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
		var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
}

char	*expand_variables(const char *str, t_command *cmd, int *arg_pos)
{
	int		pos;
	int		i;
	char	*env_val;
	char	*result;
	char	var_name[1024];

	if (cmd->interpret[*arg_pos])
		return ((char *)str);
	result = malloc(sizeof(char) * 1024);
	pos = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			extract_variable_name(str, &i, var_name);
			env_val = getenv(var_name);
			if (env_val)
			{
				ft_strcpy(result + pos, env_val);
				pos += ft_strlen(env_val);
			}
		}
		else
			result[pos++] = str[i++];
	}
	result[pos] = '\0';
	return (result);
}
