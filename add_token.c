/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:17:19 by ateca             #+#    #+#             */
/*   Updated: 2024/11/06 08:22:52 by ansebast         ###   ########.fr       */
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
		perror("malloc");
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
