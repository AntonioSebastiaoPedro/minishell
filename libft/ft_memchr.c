/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:29:38 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/10 08:48:59 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int ch, size_t num)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (num--)
		if (*ptr++ == (unsigned char)ch)
			return ((void *)ptr - 1);
	return (NULL);
}
