/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:41:26 by ateca             #+#    #+#             */
/*   Updated: 2024/11/05 18:41:27 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *env_path, const char delim, char **next_path)
{
	int	i;

	if (!env_path)
		env_path = *next_path;
	i = 0;
	while (env_path[i] != '\0' && env_path[i] != delim)
		i++;
	if (env_path[i] == delim)
	{
		env_path[i] = '\0';
		*next_path = env_path + i + 1;
	}
	else
		return (NULL);
	return (env_path);
}
