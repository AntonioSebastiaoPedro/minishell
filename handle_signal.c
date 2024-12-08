/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:21:52 by ateca             #+#    #+#             */
/*   Updated: 2024/12/08 07:51:53 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_external_command(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
}

void	handle_sigint_heredoc(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	exit(130);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
