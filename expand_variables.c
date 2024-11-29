/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:50:04 by ateca             #+#    #+#             */
/*   Updated: 2024/11/29 07:12:48 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_variable_name(const char *str, int *i, char *var_name)
{
	int	j;

	j = 0;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '?'))
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

int	handle_dollar_sign(char *str, int *i, char *result, int pos, t_env **env)
{
	char	var_name[7000000];
	char	*env_val;

	if (ft_isdigit(str[*i + 1]))
	{
		result[pos++] = str[(*i)++];
		result[pos++] = str[(*i)++];
	}
	else
	{
		extract_variable_name(str, i, var_name);
		if (ft_strcmp("?", var_name) == 0)
			env_val = get_env_value("XDG_CMD_STATUS", env);
		else
			env_val = get_env_value(var_name, env);
		check_enval(&env_val, &result, &pos);
	}
	return (pos);
}

char	*allocate_result_buffer(void)
{
	char	*result;

	result = malloc(sizeof(char) * 7000000);
	if (!result)
		perror("minishell: malloc failed");
	return (result);
}

char	*expand_variables(const char *str, t_command *cmd, int *arg_pos,
		t_env **env)
{
	int		pos;
	int		i;
	char	*result;

	if (cmd->interpret[*arg_pos])
		return (ft_strdup((char *)str));
	result = allocate_result_buffer();
	if (!result)
		return (NULL);
	pos = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			pos = handle_dollar_sign((char *)str, &i, result, pos, env);
		else
			result[pos++] = str[i++];
	}
	result[pos] = '\0';
	return (result);
}
