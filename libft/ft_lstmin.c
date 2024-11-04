/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:27:21 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/23 09:01:32 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_lstmin(t_stack *head)
{
	t_stack	*min_node;

	min_node = head;
	while (head != NULL)
	{
		if (head->value < min_node->value)
			min_node = head;
		head = head->next;
	}
	return (min_node);
}
