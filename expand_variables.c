/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:50:04 by ateca             #+#    #+#             */
/*   Updated: 2024/11/18 15:50:06 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_variable_name(char *str, int *i, char *var_name)
{
	int	j;

	j = 0;
	(*i)++;
	while (str[*i] != '\0' && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
}

int	handle_dollar_sign(char *str, int *i, char *result, int pos)
{
	char	var_name[1024];
	char	*env_val;

	if (ft_isdigit(str[*i + 1]))
	{
		result[pos++] = str[(*i)++];
		result[pos++] = str[(*i)++];
	}
	else
	{
		extract_variable_name(str, i, var_name);
		env_val = getenv(var_name);
		if (env_val)
		{
			strcpy(result + pos, env_val);
			pos += ft_strlen(env_val);
		}
	}
	return (pos);
}

char	*allocate_result_buffer(void)
{
	char	*result;

	result = malloc(sizeof(char) * 1024);
	if (!result)
		perror("malloc failed");
	return (result);
}

char	*expand_variables(char *str)
{
	int		pos;
	int		i;
	char	*result;

	result = allocate_result_buffer();
	if (!result)
		return (NULL);
	pos = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			pos = handle_dollar_sign(str, &i, result, pos);
		else
			result[pos++] = str[i++];
	}
	result[pos] = '\0';
	return (result);
}
