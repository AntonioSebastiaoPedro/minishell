/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:28:54 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/29 10:10:20 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_stack **head)
{
	t_stack	*current;
	t_stack	*next_node;

	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		ft_lstdelone(current);
		current = next_node;
	}
	*head = NULL;
}
