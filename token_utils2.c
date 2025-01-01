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

char	*expand_join(char *temp_line, int single_quote, t_token **tokens,
	t_expand_state *est)
{
	char		*expanded;
	char		*combined;

	if (!single_quote)
	{
		expanded = expand_variables(temp_line, est->env);
		if (temp_line[0] == '$' && temp_line[1] != '$'
			&& ft_strchr(expanded, ' ') && !est->recursive
			&& !ft_isspace(temp_line[1]) && temp_line[1] != '\0')
		{
			tokenize(expanded, tokens, est->env, 1);
			free(expanded);
			free(temp_line);
			free(est->result);
			return (ft_strdup(""));
		}
		free(temp_line);
		temp_line = expanded;
	}
	combined = ft_strjoin(est->result, temp_line);
	free(temp_line);
	free(est->result);
	est->result = combined;
	return (est->result);
}

char	*combine_with_next(const char *line, int *i, t_token **tokens,
	t_expand_state *est)
{
	char	*temp_line;
	int		start;
	int		single_quote;
	
	while (line[*i] && (line[*i] == '"' || line[*i] == '\''
			|| !ft_isspace(line[*i])))
	{
		single_quote = line[*i] == '\'';
		if (line[*i] == '"' || line[*i] == '\'')
			temp_line = process_quotes(line, i, line[(*i)++]);
		else
		{
			start = *i;
			while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '"'
				&& line[*i] != '\'')
				(*i)++;
			temp_line = ft_substr(line, start, *i - start);
		}
		est->result = expand_join(temp_line, single_quote, tokens, est);
	}
	return (est->result);
}

void	init_variables(int *single_quote_count, int *double_quote_count,
	int *inside_single_quotes, int *inside_double_quotes)
{
	*single_quote_count = 0;
	*double_quote_count = 0;
	*inside_single_quotes = 0;
	*inside_double_quotes = 0;
}

int	has_unclsed_quotes(const char *line, int *j)
{
	int	i;
	int	single_quote_count;
	int	double_quote_count;
	int	inside_single_quotes;
	int	inside_double_quotes;

	i = *j;
	init_variables(&single_quote_count, &double_quote_count,
		&inside_single_quotes, &inside_double_quotes);
	while (line[i])
	{
		if (line[i] == '"' && !inside_single_quotes)
		{
			double_quote_count++;
			inside_double_quotes = !inside_double_quotes;
		}
		else if (line[i] == '\'' && !inside_double_quotes)
		{
			single_quote_count++;
			inside_single_quotes = !inside_single_quotes;
		}
		i++;
	}
	return (single_quote_count % 2 != 0 || double_quote_count % 2 != 0);
}
