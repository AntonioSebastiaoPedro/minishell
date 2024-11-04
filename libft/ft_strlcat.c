/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:31:30 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/28 07:34:56 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size_dest)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	remaining;
	size_t	i;

	src_len = ft_strlen(src);
	if (size_dest == 0)
		return (src_len);
	dest_len = ft_strlen(dest);
	if (dest_len >= size_dest)
		dest_len = size_dest;
	if (dest_len == size_dest)
		return (size_dest + src_len);
	remaining = size_dest - dest_len - 1;
	i = 0;
	while (i < remaining && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + ft_strlen(src));
}
