/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:25:08 by ateca             #+#    #+#             */
/*   Updated: 2024/10/30 11:25:21 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}		t_token;

typedef struct s_command
{
	char				*command;
	char				**args;
	char				*input_redir;
	char				*output_redir;
	int					append;
	struct s_command	*next;
}		t_command;

void		tokenize(char *line, t_token **tokens);

t_token		*add_token(t_token *head, char *value);

t_command	*parse_tokens(t_token *tokens);

#endif
