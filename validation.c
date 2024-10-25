/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:47:42 by ateca             #+#    #+#             */
/*   Updated: 2024/10/25 13:47:43 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int	validate_cd(char **args)
{
	if (args[1] == NULL)
	{
		printf("cd: missing argument\n");
		return (0);
	}
	if (access(args[1], F_OK) != 0)
	{
		perror("cd");
		return (0);
	}
	return (1);
}

int	validate_exit(char **args)
{
	if (args[1] != NULL && !isdigit(args[1][0]))
	{
		printf("exit: numeric argument required\n");
		return (0);
	}
	return (1);
}

int	validate_command(char **args)
{
	if (strcmp(args[0], "cd") == 0)
		return (validate_cd(args));
	if (strcmp(args[0], "exit") == 0)
		return (validate_exit(args));
	if (strcmp(args[0], "pwd") == 0 && args[1] != NULL)
	{
		printf("pwd: too many arguments\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char	*args[] = {"cd", "non_existing_directory", NULL};

	if (validate_command(args))
		printf("Command is valid\n");
	else
		printf("Command is invalid\n");
	return (0);
}
