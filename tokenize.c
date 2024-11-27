/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:56 by ateca             #+#    #+#             */
/*   Updated: 2024/11/05 00:00:03 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection_and_pipes(char *line, int *i, t_token **tokens)
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
	int		capacity;
	char	quote;
	char	*buffer;

	j = 0;
	capacity = 256;
	buffer = malloc(sizeof(char) * capacity);
	if (!buffer)
		return ;
	quote = line[(*i)++];
	while (line[*i] && line[*i] != quote)
	{
		if (j >= capacity - 1)
		{
			buffer = realloc_token(buffer, &capacity);
			if (!buffer)
				return ;
		}
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
	(*i)++;
	free(buffer);
}

void	handle_environment_variable(const char *line, int *i, t_token **tokens)
{
	char	*buffer;
	int		j;
	int		capacity;

	j = 0;
	capacity = 256;
	buffer = malloc(sizeof(char) * capacity);
	if (!buffer)
		return ;
	buffer[j++] = line[(*i)++];
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		if (j >= capacity - 1)
		{
			buffer = realloc_token(buffer, &capacity);
			if (!buffer)
				return ;
		}
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
	free(buffer);
}

void	handle_word(const char *line, int *i, t_token **tokens)
{
	char	*buffer;
	int		j;
	int		capacity;

	j = 0;
	capacity = 256;
	buffer = malloc(sizeof(char) * capacity);
	if (!buffer)
		return ;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && line[*i]
		!= '>' && line[*i] != '<')
	{
		if (j >= capacity - 1)
		{
			buffer = realloc_token(buffer, &capacity);
			if (!buffer)
				return ;
		}
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
	free(buffer);
}

void	tokenize(char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '|' && check_isspace(line, i))
			handle_pipe_stdin(line, tokens, &i);
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			handle_redirection_and_pipes(line, &i, tokens);
		else if (line[i] == '"' || line[i] == '\'')
			handle_quotes(line, &i, tokens);
		else if (line[i] == '$')
			handle_environment_variable(line, &i, tokens);
		else if (line[i])
			handle_word(line, &i, tokens);
	}
}
