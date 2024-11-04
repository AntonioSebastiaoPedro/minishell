/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstupdateindx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 05:49:47 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/29 05:49:53 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstupdateindx(t_stack *head)
{
	int		index;
	t_stack	*current;

	index = 0;
	current = head;
	while (current != NULL)
	{
		current->index = index;
		index++;
		current = current->next;
	}
}
