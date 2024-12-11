/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:56 by ateca             #+#    #+#             */
/*   Updated: 2024/11/22 14:30:48 by ansebast         ###   ########.fr       */
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

void	handle_quotes(const char *line, int *i, t_token **tokens, t_env **env)
{
	char	quote;
	int		is_quote_double;
	char	*buffer;

	quote = line[(*i)++];
	is_quote_double = (quote == '"');
	buffer = process_quotes(line, i, quote);
	if (!buffer)
		return ;
	buffer = combine_with_next(line, i, buffer);
	if (!buffer)
		return ;
	buffer = expand_or_add_token(buffer, is_quote_double, tokens, env);
	free(buffer);
	buffer = NULL;
}

void	handle_envi_var(const char *line, int *i, t_token **tokens, t_env **env)
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
	buffer = expand_variables(buffer, NULL, 0, env);
	tokenize(buffer, tokens, env);
	free(buffer);
	isspace_add(line, i, tokens, &buffer);
}

void	isspace_add(const char *line, int *i, t_token **tokens, char **buffer)
{
	(*buffer) = NULL;
	if (line[(*i)] && ft_isspace(line[(*i)]))
	{
		add_token(*tokens, " ", 0);
		(*i)++;
	}
}

void	tokenize(char *line, t_token **tokens, t_env **envp)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (is_command_pipe(line, i, *tokens))
			handle_pipe_stdin(line, tokens, &i, envp);
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			handle_redirection_and_pipes(line, &i, tokens);
		else if (line[i] == '\'' || line[i] == '"')
			handle_quotes(line, &i, tokens, envp);
		else if (line[i] == '$' && line[i + 1] != '\0' && line[i + 1] != '?')
			handle_envi_var(line, &i, tokens, envp);
		else if (line[i])
			handle_word(line, &i, tokens);
	}
}
