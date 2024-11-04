/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:31:04 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/27 13:37:11 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*str2;
	size_t	size;

	size = ft_strlen(str) + 1;
	str2 = (char *)ft_calloc(1, size);
	if (!str2)
		return (NULL);
	ft_memcpy(str2, str, size);
	return (str2);
}
