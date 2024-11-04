/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:05 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/15 07:37:54 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;

	s = NULL;
	while (*str)
	{
		if (*str == (char)c)
			s = ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		s = ((char *)str);
	return (s);
}
