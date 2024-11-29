/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:30:37 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/29 07:11:05 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	interpret_quotes(const char *line, int *i, int *dob_quote, int *sin_quote, int *interpret)
{
	if (line[*i] == '\"' && !sin_quote)
	{
		*dob_quote = !*dob_quote;
		(*i)++;
		if (*dob_quote)
			*interpret = 0;
		return (1);
	}
	if (line[*i] == '\'' && !*dob_quote)
	{
		*sin_quote = !*sin_quote;
		(*i)++;
		if (*sin_quote)
			*interpret = 1;
		return (1);
	}
	return (0);
}


void	handle_word(const char *line, int *i, t_token **tokens)
{
	char	buffer[7000000];
	int		j;
	int		interpret;
	int		dob_quote;
	int		sin_quote;

	j = 0;
	interpret = 0;
	dob_quote = 0;
	sin_quote = 0;
	while (line[*i] && !is_special_char(line[*i]))
	{
		if (interpret_quotes(line, i, &dob_quote, &sin_quote, &interpret))
			continue;
		if (ft_isspace(line[*i]) && !dob_quote && !sin_quote)
			break;
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer, interpret);
}