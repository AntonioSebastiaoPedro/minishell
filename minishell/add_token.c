/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:17:19 by ateca             #+#    #+#             */
/*   Updated: 2024/10/30 14:17:21 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
