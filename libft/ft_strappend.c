/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 02:33:06 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/18 02:36:55 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(dest[j])
		j++;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest);
}