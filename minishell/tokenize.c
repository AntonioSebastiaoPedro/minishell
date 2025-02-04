/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:56 by ateca             #+#    #+#             */
/*   Updated: 2024/10/30 14:06:57 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection_and_pipes(const char *line, int *i, t_token **tokens)
{
	char	operator[2];

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*tokens) = add_token(*tokens, ">>");
		*i += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*tokens) = add_token(*tokens, "<<");
		*i += 2;
	}
	else
	{
		operator[0] = line[*i];
		operator[1] = '\0';
		(*tokens) = add_token(*tokens, operator);
		(*i)++;
	}
}

void	handle_quotes(const char *line, int *i, t_token **tokens)
{
	int		j;
	char	quote;
	char	buffer[256];

	j = 0;
	quote = line[(*i)++];
	while (line[*i] && line[*i] != quote)
	{
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
	(*i)++;
}

void	handle_environment_variable(const char *line, int *i, t_token **tokens)
{
	char	buffer[256];
	int		j;

	j = 0;
	buffer[j++] = line[(*i)++];
	while (isalnum(line[*i]) || line[*i] == '_')
	{
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
}

void	handle_word(const char *line, int *i, t_token **tokens)
{
	char	buffer[256];
	int		j;

	j = 0;
	while (line[*i] && !isspace(line[*i]) && line[*i] != '|' && line[*i]
		!= '>' && line[*i] != '<')
	{
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
}

void	tokenize(char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (isspace(line[i]))
			i++;
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			handle_redirection_and_pipes(line, &i, tokens);
		else if (line[i] == '"' || line[i] == '\'')
			handle_quotes(line, &i, tokens);
		else if (line[i] == '$')
			handle_environment_variable(line, &i, tokens);
		else if (line[i])
			handle_word(line, &i, tokens);
	}
}
