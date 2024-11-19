/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:28:48 by ateca             #+#    #+#             */
/*   Updated: 2024/11/19 15:28:50 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(const char *token)
{
	return (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}

void	handle_redirection(t_token *token, t_command *current_cmd)
{
	if (ft_strcmp(token->value, ">") == 0 && token->next != NULL)
		current_cmd->output_redir = token->next->value;
	else if (ft_strcmp(token->value, "<") == 0 && token->next != NULL)
		current_cmd->input_redir = token->next->value;
	else if (ft_strcmp(token->value, ">>") == 0 && token->next != NULL)
	{
		current_cmd->output_redir = token->next->value;
		current_cmd->append = 1;
	}
	else if (ft_strcmp(token->value, "<<") == 0 && token->next != NULL)
	{
		current_cmd->input_redir = token->next->value;
		current_cmd->heredoc = 1;
	}
}

int	handle_redirections(t_command **cmd)
{
	if ((*cmd)->input_redir != NULL)
		return (handle_input_redirection(*cmd));
	else if ((*cmd)->output_redir != NULL)
		return (handle_output_redirection(cmd));
	return (0);
}

void	case_redirection_print_message_error(char *operator)
{
	if (ft_strcmp(operator, ">") == 0 || ft_strcmp(operator, "<") == 0
		|| ft_strcmp(operator, ">>") == 0 || ft_strcmp(operator, "<<") == 0)
	{
		write(2, "bash: syntax error near unexpected token `newline'", 50);
		write(2, "\n", 1);
	}
	else if (ft_strcmp(operator, "|") == 0)
		write(2, "bash: syntax error near unexpected token `|'\n", 45);
}
