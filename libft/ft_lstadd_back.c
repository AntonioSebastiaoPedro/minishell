/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:28:43 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/29 10:10:13 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_stack **head, t_stack *new_node)
{
	t_stack	*last;

	if (head && *head)
	{
		last = ft_lstlast(*head);
		last->next = new_node;
		new_node->index = last->index + 1;
		new_node->next = NULL;
	}
	else
		*head = new_node;
}
