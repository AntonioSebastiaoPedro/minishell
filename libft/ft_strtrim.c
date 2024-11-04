/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:13 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/10 11:17:23 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isinstr(char c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trim;

	if (!s || !set)
		return (NULL);
	start = 0;
	while (s[start] && isinstr(s[start], set))
		start++;
	end = ft_strlen(s) - 1;
	while (end > start && isinstr(s[end], set))
		end--;
	len = end - start + 1;
	trim = (char *)ft_calloc(len + 1, sizeof(char));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, s + start, len + 1);
	return (trim);
}
