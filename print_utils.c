/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:34:35 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/07 20:41:27 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		printf("Token: %s\n", temp->value);
		printf("Interpret: %d\n", temp->interpret);
		temp = temp->next;
	}
}

void	print_commands(t_command *commands)
{
	int			i;
	t_command	*temp;

	temp = commands;
	printf("\n\n");
	while (temp)
	{
		printf("command: %s\n", temp->command);
		if (temp->args)
		{
			i = -1;
			printf("args:");
			while (temp->args[++i] != NULL)
				printf(" %s", temp->args[i]);
			printf("\n");
		}
		printf("input_redir: %s\n", temp->input_redir);
		printf("output_redir: %s\n", temp->output_redir);
		temp = temp->next;
		printf("\n\n");
	}
}
