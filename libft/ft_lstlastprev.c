/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlastprev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:02:00 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/28 10:11:30 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_lstlastprev(t_stack *head)
{
	t_stack	*curr;

	if (head == NULL || head->next == NULL)
		return (NULL);
	curr = head;
	while (curr->next->next)
		curr = curr->next;
	return (curr);
}
