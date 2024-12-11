/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:17:19 by ateca             #+#    #+#             */
/*   Updated: 2024/11/28 15:14:42 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_token(t_token *head, char *value, int interpret)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("minishell: malloc failed");
		return (NULL);
	}
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	new_token->interpret = interpret;
	if (!head)
		return (new_token);
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	return (head);
}

t_token	*ft_lstlast_token(t_token *head)
{
	if (head)
		while (head->next)
			head = head->next;
	return (head);
}

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens != NULL)
	{
		next = tokens->next;
		if (tokens->value)
		{
			free(tokens->value);
			tokens->value = NULL;
		}
		free(tokens);
		tokens = next;
	}
}

char	*realloc_token(char *buffer, int *capacity)
{
	char	*new_buffer;
	int		old_capacity;

	old_capacity = *capacity;
	(*capacity) *= 2;
	new_buffer = ft_realloc(buffer, old_capacity, sizeof(char) * (*capacity));
	if (!new_buffer)
	{
		perror("minishell: realloc failed");
		return (NULL);
	}
	return (new_buffer);
}

char	*process_quotes(const char *line, int *i, char quote)
{
	int		capacity;
	int		j;
	char	*buffer;

	capacity = 256;
	j = 0;
	buffer = malloc(sizeof(char) * capacity);
	if (!buffer)
		return (NULL);
	while (line[*i] && line[*i] != quote)
	{
		if (j >= capacity - 1)
		{
			buffer = realloc_token(buffer, &capacity);
			if (!buffer)
				return (NULL);
		}
		buffer[j++] = line[(*i)++];
	}
	if (line[*i] != quote)
		return (print_error_unclosed_quote(buffer, quote));
	(*i)++;
	buffer[j] = '\0';
	return (buffer);
}
