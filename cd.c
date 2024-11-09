/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:40:15 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/09 19:22:14 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **args, t_env **env)
{
	char	*path;

	path = get_env_value("HOME", env, ft_strcmp);
	if (args)
		if (args[0])
			path = args[0];
	if (chdir(path) == -1)
		perror("cd");
}
