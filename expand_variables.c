/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:50:04 by ateca             #+#    #+#             */
/*   Updated: 2024/11/22 12:32:53 by ansebast         ###   ########.fr       */
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

int	handle_dollar_sign(char *str, int *i, t_expand_state *state)
{
	char	var_name[2097152];
	char	*env_val;

	if (ft_isdigit(str[*i + 1]))
	{
		state->result[state->pos++] = str[(*i)++];
		state->result[state->pos++] = str[(*i)++];
	}
	else
	{
		extract_variable_name(str, i, var_name);
		if (ft_strcmp("?", var_name) == 0)
			env_val = get_env_value("XDG_CMD_STATUS", state->env);
		else
			env_val = get_env_value(var_name, state->env);
		check_enval(&env_val, &(state->result), &(state->pos));
	}
	return (state->pos);
}

char	*allocate_result_buffer(char *str)
{
	char	*result;
	size_t	capacity;
	
	capacity = 2097152;
	if (ft_strlen(str) >= capacity)
	{
		perror("Minishell: argument size exceeded");
		return (NULL);
	}
	result = malloc(sizeof(char) * capacity);
	if (!result)
		perror("minishell: malloc failed");
	return (result);
}

char	*expand_variables(char *str, t_command *cmd, int *arg_pos, t_env **env)
{
	int				i;
	char			*result;
	t_expand_state	state;

	i = 0;
	if (cmd->interpret[*arg_pos])
		return (ft_strdup(str));
	result = allocate_result_buffer(str);
	if (!result)
		return (NULL);
	state.result = result;
	state.pos = 0;
	state.env = env;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			handle_dollar_sign(str, &i, &state);
		else
			state.result[state.pos++] = str[i++];
	}
	state.result[state.pos] = '\0';
	return (state.result);
}
