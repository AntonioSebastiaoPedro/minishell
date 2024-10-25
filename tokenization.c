/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:09:53 by ateca             #+#    #+#             */
/*   Updated: 2024/10/25 14:09:55 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}		t_token;

// Função para adicionar um token ao final da lista
t_token	*add_token(t_token *head, char *value)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("malloc");
		return (NULL);
	}	
	new_token->value = strdup(value);
	new_token->next = NULL;
	if (!head)
		return (new_token);
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	return (head);
}

// Ignora espaços em branco
void	ignore_whitespace(char *line, int *i)
{
	while (isspace(line[*i]))
		(*i)++;
}

// Redirecionadores e pipes >, <, >>, << e |
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

// Lida com aspas simples e duplas "" ''
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
	(*i)++; // Pula a aspas de fechamento
}

// Lida com variáveis de ambiente $PATH
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

// Captura palavras normais
void	handle_word(const char *line, int *i, t_token **tokens)
{
	char	buffer[256];
	int		j;

	j = 0;
	while (line[*i] && !isspace(line[*i]) && line[*i] != '|' && line[*i] != '>' && line[*i] != '<')
	{
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	(*tokens) = add_token(*tokens, buffer);
}

// Separar a sequência de texto em partes menores
void	tokenize(char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		ignore_whitespace(line, &i);
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

// Exibir tokens
void	print_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		printf("Token: %s\n", temp->value);
		temp = temp->next;
	}
}

int	main(void)
{
	char	line[] = "echo \"Hello | World\" $PATH | grep minishell >> output.txt";
	t_token	*tokens;

	tokens = NULL;
	tokenize(line, &tokens);
	print_tokens(tokens);
	return (0);
}
