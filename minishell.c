/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:19 by ateca             #+#    #+#             */
/*   Updated: 2024/11/27 11:43:38 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line;
	t_env		*env_dup;
	t_token		*tokens;
	t_command	*commands;
	extern char	**environ;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	env_dup = NULL;
	envcpy(&env_dup, environ);
	update_shlvl(&env_dup);
	while (1)
	{
		tokens = NULL;
		// line = readline("\001\033[38;5;81mateca\033[0m@\033[38;5;208mansebast\033[0m-\033[38;5;196mAkatsuki\033[0m🌊🔥$\002 ");
		line = readline("Akatsuki$ ");
		if (!line)
			break ;
		add_history(line);
		tokenize(line, &tokens);
		commands = parse_tokens(tokens);
		// print_tokens(tokens);
		// print_commands(commands);
		execute_commands(commands, &env_dup);
		free(line);
		printf("%d\n", *env_dup->var);
		free_tokens(tokens);
		free_commands(commands);
	}
	rl_clear_history();
	free_env(&env_dup);
	return (0);
}
