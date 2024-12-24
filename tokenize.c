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

void	handle_line(const char *line, int *i, t_token **tokens, t_env **envp)
{
	char			quote;
	int				is_quote_double;
	char			*buffer;
	t_expand_state	est;
	
	est.pos = 0;
	est.env = envp;
	est.result = ft_strdup("");
	if (has_unclsed_quotes(line, i))
	{
		print_error_unclosed_quote(NULL, '\0', line, i);
		return ;
	}
	quote = line[(*i)];
	is_quote_double = (quote == '"') && !(*tokens);
	buffer = combine_with_next(line, i, tokens, &est);
	if (!buffer)
	{
		(*i) = ft_strlen(line);
		perror("minishell: malloc failed");
		return ;
	}
	if (ft_strcmp(buffer, "") != 0)
		(*tokens) = add_token(*tokens, buffer, is_quote_double);
	free(buffer);
	buffer = NULL;
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
			handle_line(line, &i, tokens, envp);
		else if (line[i] == '$' && line[i + 1] != '\0' && !is_recursive)
			handle_line(line, &i, tokens, envp);
		else if (line[i])
			handle_line(line, &i, tokens, envp);
	}
}
