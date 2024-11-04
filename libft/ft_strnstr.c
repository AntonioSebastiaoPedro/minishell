/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:00 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/14 19:05:21 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t num)
{
	size_t	i;
	size_t	len_sub;

	len_sub = ft_strlen(str2);
	i = 0;
	if (len_sub == 0)
		return ((char *)str1);
	while (i < num && str1[i])
	{
		if (str1[i] == str2[0])
		{
			if ((num - i) >= len_sub)
				if (ft_strncmp(str2, str1 + i, len_sub) == 0)
					return ((char *)&str1[i]);
		}
		i++;
	}
	return (NULL);
}
