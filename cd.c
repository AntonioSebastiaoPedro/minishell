/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:40:15 by ansebast          #+#    #+#             */
/*   Updated: 2024/12/08 08:55:05 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_cd(char *path);

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	*cwd;
	char	*msg_err;

	path = NULL;
	if (args)
		if (args[0])
			path = args[0];
	if (!path)
	{
		msg_err = "minishell: cd: with only a relative or absolute path\n";
		write(2, msg_err, ft_strlen(msg_err));
		return (1);
	}
	else if (ft_tablen(args) > 1)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	else if (chdir(path) == -1)
	{
		print_error_cd(path);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	update_envvar(env, "OLDPWD", get_env_value("PWD", env));
	update_envvar(env, "PWD", cwd);
	free(cwd);
	return (0);
}

void	print_error_cd(char *path)
{
	char	*program_name;
	char	*colon_space;
	char	*newline;
	char	*error_message;

	program_name = "minishell: cd: ";
	colon_space = ": ";
	newline = "\n";
	error_message = strerror(errno);
	write(2, program_name, ft_strlen(program_name));
	write(2, path, ft_strlen(path));
	write(2, colon_space, ft_strlen(colon_space));
	write(2, error_message, ft_strlen(error_message));
	write(2, newline, ft_strlen(newline));
}
