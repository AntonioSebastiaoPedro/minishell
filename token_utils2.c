/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:48 by ateca             #+#    #+#             */
/*   Updated: 2024/12/07 14:36:50 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*combine_with_next(const char *line, int *i, char *buffer)
{
	char	*temp;
	char	*combined;
	int		start;

	while (line[*i] && (line[*i] == '"' || line[*i] == '\''
			|| !ft_isspace(line[*i])))
	{
		if (line[*i] == '"' || line[*i] == '\'')
			temp = process_quotes(line, i, line[(*i)++]);
		else
		{
			start = *i;
			while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '"'
				&& line[*i] != '\'')
				(*i)++;
			temp = ft_substr(line, start, *i - start);
		}
		combined = ft_strjoin(buffer, temp);
		free(buffer);
		free(temp);
		buffer = combined;
	}
	return (buffer);
}

char	*expand_or_add_token(char *buffer, int is_quote_doub, t_token **tokens,
	t_env **env)
{
	char	*temp;

	if (is_quote_doub && buffer[0] == '$')
	{
		temp = expand_variables(buffer, NULL, 0, env);
		free(buffer);
		buffer = temp;
		if (!buffer)
			return (NULL);
		tokenize(buffer, tokens, env);
	}
	else
	{
		(*tokens) = add_token(*tokens, buffer, 0);
	}
	return (buffer);
}
