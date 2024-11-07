/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:19 by ateca             #+#    #+#             */
/*   Updated: 2024/11/07 20:38:03 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_env		*env_dup;
	t_token		*tokens;
	t_command	*commands;

	(void)ac;
	(void)av;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	env_dup = NULL;
	envcpy(&env_dup, env);
	while (1)
	{
		tokens = NULL;
		line = readline("akatsuki❟❛❟🥷🏻☁🩸> ");
		if (!line)
			break ;
		add_history(line);
		tokenize(line, &tokens);
		commands = parse_tokens(tokens);
		// print_tokens(tokens);
		// print_commands(commands);
		execute_commands(commands, env_dup);
		free(line);
		free_tokens(tokens);
		free_commands(commands);
	}
	rl_clear_history();
	return (0);
}
