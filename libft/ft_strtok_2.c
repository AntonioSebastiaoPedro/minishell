/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:07:42 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/18 01:29:13 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_2(char *str, const char *delimiter)
{
	static char	*current_position;
	char		*token_start;

	if (str != NULL)
		current_position = str;
	if (current_position == NULL)
		return (NULL);
	while (*current_position && ft_strchr(delimiter, *current_position))
		current_position++;
	if (*current_position == '\0')
		return (NULL);
	token_start = current_position;
	while (*current_position && !ft_strchr(delimiter, *current_position))
		current_position++;
	if (*current_position)
	{
		*current_position = '\0';
		current_position++;
	}
	return (token_start);
}
