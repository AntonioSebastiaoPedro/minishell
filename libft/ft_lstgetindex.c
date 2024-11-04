/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetindex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 05:50:44 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/31 20:50:33 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstgetindex(t_stack **head, t_stack *value)
{
	t_stack	*current;

	current = *head;
	while (current != NULL)
	{
		if (current == value)
			return (value->index);
		current = current->next;
	}
	return (-1);
}
