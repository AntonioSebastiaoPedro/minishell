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

	if (!buffer)
		return (NULL);
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
		tokenize(buffer, tokens, env, 0);
	}
	else
	{
		(*tokens) = add_token(*tokens, buffer, 2);
	}
	return (buffer);
}

int	has_unclsed_quotes(const char *line, int *j)
{
	int	i;
	int	single_quote_count;
	int	double_quote_count;
	int	inside_double_quotes;

	i = *j;
	single_quote_count = 0;
	double_quote_count = 0;
	inside_double_quotes = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			double_quote_count++;
			inside_double_quotes = !inside_double_quotes;
		}
		else if (line[i] == '\'' && !inside_double_quotes)
			single_quote_count++;
		i++;
	}
	if (single_quote_count % 2 != 0 || double_quote_count % 2 != 0)
		return (1);
	return (0);
}
