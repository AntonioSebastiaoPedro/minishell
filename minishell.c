/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:19 by ateca             #+#    #+#             */
/*   Updated: 2024/12/07 19:11:41 by ansebast         ###   ########.fr       */
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
	signal(SIGQUIT, SIG_IGN);
	env_dup = NULL;
	envcpy(&env_dup, environ);
	update_shlvl(&env_dup);
	while (1)
	{
		tokens = NULL;
		line = readline("Akatsuki> ");
		if (!line)
			break ;
		add_history(line);
		tokenize(line, &tokens, &env_dup);
		free(line);
		commands = parse_tokens(tokens);
		print_tokens(tokens);
		//print_commands(commands);
		execute_commands(commands, &env_dup);
		free_tokens(tokens);
		free_commands(commands);
	}
	rl_clear_history();
	free_env(&env_dup);
	return (0);
}
