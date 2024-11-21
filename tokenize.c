/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:56 by ateca             #+#    #+#             */
/*   Updated: 2024/11/21 22:27:40 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection_and_pipes(const char *line, int *i, t_token **tokens)
{
	char	operator[2];

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*tokens) = add_token(*tokens, ">>", 0);
		*i += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*tokens) = add_token(*tokens, "<<", 0);
		*i += 2;
	}
	else
	{
		operator[0] = line[*i];
		operator[1] = '\0';
		(*tokens) = add_token(*tokens, operator, 0);
		(*i)++;
	}
}

void	handle_quotes(const char *line, int *i, t_token **tokens)
{
	int		j;
	int		interpret;
	char	quote;
	char	buffer[70000];

	j = 0;
	interpret = 0;
	quote = line[(*i)++];
	if (quote == '\'')
		interpret = 1;
	while (line[*i] && line[*i] != quote)
	{
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer, interpret);
	(*i)++;
}

void	handle_environment_variable(const char *line, int *i, t_token **tokens)
{
	char	buffer[70000];
	int		j;

	j = 0;
	buffer[j++] = line[(*i)++];
	while (ft_isalnum(line[*i]) || line[*i] == '_' || line[*i] == '?')
	{
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer, 0);
}

void	handle_word(const char *line, int *i, t_token **tokens)
{
	char	buffer[70000];
	int		j;
	int		dob_quote;
	int		sin_quote;
	int		interpret;

	j = 0;
	interpret = 0;
	dob_quote = 0;
	sin_quote = 0;
	while (line[*i] && line[*i] != '|' && line[*i] != '>' && line[*i] != '<')
	{
		if (ft_isspace(line[*i]) && !dob_quote && !sin_quote)
			break ;
		if (line[*i] == '\"')
		{
			if (!sin_quote)
				(*i)++;
			dob_quote = !dob_quote;
			if (!sin_quote)
			{
				interpret = 0;
			}
		}
		if (line[*i] == '\'')
		{
			if (!dob_quote)
				(*i)++;
			sin_quote = !sin_quote;
			if (!dob_quote)
			{
				interpret = 1;
			}
		}
		if (ft_isspace(line[*i]) && !dob_quote && !sin_quote)
			break ;
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer, interpret);
}

void	tokenize(char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			handle_redirection_and_pipes(line, &i, tokens);
		else if (line[i] == '\'' || line[i] == '"')
			handle_quotes(line, &i, tokens);
		else if (line[i] == '$')
			handle_environment_variable(line, &i, tokens);
		else if (line[i])
			handle_word(line, &i, tokens);
	}
}
