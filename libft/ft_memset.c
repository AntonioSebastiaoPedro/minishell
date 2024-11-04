/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:30:01 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/14 19:04:19 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *first, int value, size_t num)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)first;
	while (num--)
		*ptr++ = (unsigned char)value;
	return (first);
}
