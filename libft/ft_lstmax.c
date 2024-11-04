/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 05:51:14 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/29 10:12:55 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_lstmax(t_stack *head)
{
	t_stack	*max_node;

	max_node = head;
	while (head != NULL)
	{
		if (head->value > max_node->value)
			max_node = head;
		head = head->next;
	}
	return (max_node);
}
