/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:28:48 by ateca             #+#    #+#             */
/*   Updated: 2025/01/09 18:46:23 by ansebast         ###   ########.fr       */
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

int	handle_redirections(t_command **cmd, t_status_cmd *st, pid_t *pids, int *i)
{
	int	result;

	result = 0;
	if ((*cmd)->input_redir != NULL)
	{
		result = handle_input_redirection(cmd, st->original_stdout,
				&st->status, st);
		if (result == -3)
		{
			pids[(*i)] = -1;
			(*i)++;
		}
	}
	else if ((*cmd)->output_redir != NULL)
	{
		result = handle_output_redirection(cmd, &st->status);
		if (result == -3)
		{
			*cmd = (*cmd)->next;
			pids[(*i)] = -1;
			(*i)++;
		}
	}
	return (result);
}
