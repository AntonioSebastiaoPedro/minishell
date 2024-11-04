/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:28:38 by ansebast          #+#    #+#             */
/*   Updated: 2024/08/27 13:35:55 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_countnbr(long nbr)
{
	long	count;

	count = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		count++;
	}
	while (nbr)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int nbr)
{
	char	*number;
	int		count;
	long	n;

	n = nbr;
	count = ft_countnbr(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	number = (char *)ft_calloc((count + 1), sizeof(char));
	if (n < 0)
	{
		n = -n;
		number[0] = '-';
	}
	number[count] = '\0';
	while (n != 0)
	{
		--count;
		number[count] = (n % 10) + '0';
		n /= 10;
	}
	return (number);
}
