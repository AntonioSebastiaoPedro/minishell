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
	{
		perror("minishell: malloc failed");
		return ;
	}
	buffer = combine_with_next(line, i, buffer);
	if (!buffer)
	{
		perror("minishell: malloc failed");
		return ;
	}
	buffer = expand_or_add_token(buffer, is_quote_double, tokens, env);
	free(buffer);
	buffer = NULL;
}

char	*extract_variable(const char *line, int *i)
{
	char	*buffer;
	char	*new_buffer;
	int		j;
	int		capacity;

	capacity = 256;
	buffer = malloc(sizeof(char) * capacity);
	if (!buffer)
		return (NULL);
	j = 0;
	buffer[j++] = line[(*i)++];
	while (line[*i])
	{
		if (j >= capacity - 1)
		{
			new_buffer = realloc_token(buffer, &capacity);
			if (!new_buffer)
				return (NULL);
			buffer = new_buffer;
		}
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	return (buffer);
}

void	handle_envi_var(const char *line, int *i, t_token **tokens, t_env **env)
{
	char	*expanded_buffer;
	char	*buffer;

	buffer = extract_variable(line, i);
	if (!buffer)
	{
		perror("minishell: malloc failed");
		return ;
	}
	expanded_buffer = expand_variables(buffer, NULL, 0, env);
	if (expanded_buffer != buffer)
		free(buffer);
	tokenize(expanded_buffer, tokens, env, 1);
	free(expanded_buffer);
}

void	tokenize(char *line, t_token **tokens, t_env **envp, int is_recursive)
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
		else if (ft_strchr(&line[i], '$') && line[i + 1] != '\0'
			&& !is_recursive)
			handle_envi_var(line, &i, tokens, envp);
		else if (line[i])
			handle_word(line, &i, tokens);
	}
}
