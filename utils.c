/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:41:49 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/05 13:32:42 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(const char *str)
{
	char	*new_str;
	size_t	len;

	new_str = ft_strdup(str);
	if (str[0] == '\'' || str[0] == '"')
	{
		len = ft_strlen(new_str);
		if (new_str[len - 1] == str[0])
		{
			new_str[len - 1] = '\0';
			new_str++;
		}
	}
	return (new_str);
}

int	get_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}