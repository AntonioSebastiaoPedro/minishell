/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:30:37 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/22 14:30:59 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '$');
}

int	interpret_quotes(const char *line, int *i, t_quote_state *state)
{
	if (line[*i] == '\"' && !state->sin_quote)
	{
		state->dob_quote = !state->dob_quote;
		(*i)++;
		if (state->dob_quote)
			state->interpret = 0;
		return (1);
	}
	if (line[*i] == '\'' && !state->dob_quote)
	{
		state->sin_quote = !state->sin_quote;
		(*i)++;
		if (state->sin_quote)
			state->interpret = 1;
		return (1);
	}
	return (0);
}

char	*expand_buffer(char *buffer, int *capacity)
{
	int	old_capacity;

	old_capacity = *capacity;
	(*capacity) *= 2;
	buffer = ft_realloc(buffer, old_capacity, sizeof(char) * (*capacity));
	if (!buffer)
		return (NULL);
	return (buffer);
}

char	*extract_word(const char *line, int *i, t_quote_state *state)
{
	char	*buffer;
	int		j;
	int		capacity;

	j = 0;
	capacity = 256;
	buffer = malloc(sizeof(char) * capacity);
	if (!buffer)
		return (NULL);
	while (line[*i] && !is_special_char(line[*i]))
	{
		if (interpret_quotes(line, i, state))
			continue ;
		if (ft_isspace(line[*i]) && !state->dob_quote && !state->sin_quote)
			break ;
		if (j >= capacity - 1)
		{
			buffer = expand_buffer(buffer, &capacity);
			if (!buffer)
				return (NULL);
		}
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	return (buffer);
}

void	handle_word(const char *line, int *i, t_token **tokens)
{
	char			*word;
	t_quote_state	state;

	state.dob_quote = 0;
	state.sin_quote = 0;
	state.interpret = 0;
	word = extract_word(line, i, &state);
	if (!word)
		return ;
	(*tokens) = add_token(*tokens, word, state.interpret);
	free(word);
	word = NULL;
}
