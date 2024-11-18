/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:40:15 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/18 02:41:25 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	*cwd;

	path = get_env_value("HOME", env);
	if (args)
		if (args[0])
			path = args[0];
	if (chdir(path) == -1)
		perror("cd");
	cwd = getcwd(NULL, 0);
	update_envvar(env, "OLDPWD", get_env_value("PWD", env));
	update_envvar(env, "PWD", cwd);
	free(cwd);
}
