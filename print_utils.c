/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:34:35 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/08 11:49:06 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_check_cmd(char *exec_path, t_command *cmd)
{
	char	*msg;

	if (!exec_path)
	{
		msg = ": command not found";
		write(2, cmd->command, ft_strlen(cmd->command));
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
		exit(127);
	}
}

char	*print_error_unclosed_quote(char *buffer, char quote)
{
	char	*message_error;

	message_error = "minishell: syntax error: unclosed quote ";
	write(2, message_error, ft_strlen(message_error));
	write(2, &quote, 1);
	write(2, "\n", 1);
	free(buffer);
	return (NULL);
}

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
			{
				printf("%s ", temp->args[i]);
				printf("\nInterpret: %d\n", temp->interpret[i]);
			}
			printf("\n");
		}
		printf("input_redir: %s\n", temp->input_redir);
		printf("output_redir: %s\n", temp->output_redir);
		temp = temp->next;
		printf("\n\n");
	}
}
