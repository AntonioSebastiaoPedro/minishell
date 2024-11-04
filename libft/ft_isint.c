/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 00:41:25 by ansebast          #+#    #+#             */
/*   Updated: 2024/09/01 00:41:59 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *str)
{
	char	*endptr;
	long	val;

	if (*str == '\0' || (*str == '-' && *(str + 1) == '\0') || (*str == '+'
			&& *(str + 1) == '\0'))
		return (0);
	val = ft_strtol(str, &endptr);
	if (*endptr != '\0' || val < -2147483648 || val > 2147483647)
		return (0);
	return (1);
}
