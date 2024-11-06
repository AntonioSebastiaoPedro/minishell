/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:25:08 by ateca             #+#    #+#             */
/*   Updated: 2024/11/06 11:29:55 by ansebast         ###   ########.fr       */
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
# include "libft/libft.h"

typedef struct s_token
{
	char			*value;
	int		interpret;
	struct s_token	*next;
}		t_token;

typedef struct s_command
{
	char				*command;
	char				**args;
	char				*input_redir;
	char				*output_redir;
	int					append;
	int					*interpret;
	struct s_command	*next;
}		t_command;

void		tokenize(char *line, t_token **tokens);
t_token		*add_token(t_token *head, char *value, int interpret);
t_command	*parse_tokens(t_token *tokens);
char		*remove_quotes(const char *str);
void		ft_echo(char **args);
void		ft_pwd(void);
void		ft_cd(char **args);
void		ft_export(char **args);
int		ft_env(t_command *cmd, char **env);

#endif
