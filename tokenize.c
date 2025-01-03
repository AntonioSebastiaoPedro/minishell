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

void	handle_line(const char *line, int *i, t_token **tokens,
	t_expand_state *est)
{
	char	quote;
	int		is_quote;
	char	*buffer;

	est->result = ft_strdup("");
	if (has_unclsed_quotes(line, i))
	{
		print_error_unclosed_quote(NULL, '\0', line, i);
		return ;
	}
	quote = line[(*i)];
	is_quote = ((quote == '\'') || (quote == '"'));
	buffer = combine_with_next(line, i, tokens, est);
	if (!buffer)
	{
		(*i) = ft_strlen(line);
		perror("minishell: malloc failed");
		return ;
	}
	if (ft_strcmp(buffer, "") != 0)
		(*tokens) = add_token(*tokens, buffer, is_quote);
	free(buffer);
	buffer = NULL;
}

int	front_isspace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	add_quote(int *i, t_token **tokens)
{
	(*tokens) = add_token(*tokens, "''", 0);
	*i += 2;
}

void	tokenize(char *line, t_token **tokens, t_env **envp, int is_recursive)
{
	t_expand_state	est;
	int				i;

	i = 0;
	est.env = envp;
	est.recursive = is_recursive;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (is_command_pipe(line, i, *tokens))
			handle_pipe_stdin(line, tokens, &i, envp);
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			handle_redirection_and_pipes(line, &i, tokens);
		else if (((line[i] == '\'' && line[i + 1] == '\'') || (line[i] == '"'
					&& line[i + 1] == '"')) && front_isspace(&line[i] + 2))
			add_quote(&i, tokens);
		else if (line[i] == '\'' || line[i] == '"')
			handle_line(line, &i, tokens, &est);
		else if (line[i] == '$' && line[i + 1] != '\0')
			handle_line(line, &i, tokens, &est);
		else if (line[i])
			handle_line(line, &i, tokens, &est);
	}
}
