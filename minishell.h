/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:25:08 by ateca             #+#    #+#             */
/*   Updated: 2024/11/05 07:43:12 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

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
	int					heredoc;
	int					write_pipe_fd;
	int					read_pipe_fd;
	struct s_command	*next;
}		t_command;

#ifndef G_CHILD_PID_H
# define G_CHILD_PID_H
//extern pid_t	g_child_pid;
#endif

void		tokenize(char *line, t_token **tokens);
t_token		*add_token(t_token *head, char *value);
t_command	*parse_tokens(t_token *tokens);
int			execute_commands(t_command *cmd, char **envp);
int			is_builtin(char *cmd);
void		exec_builtin(t_command *cmd);
char		*expand_variables(char *str);
int			handle_redirections(t_command **cmd);
int			execute_external_command(t_command *cmd, char **envp);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		handle_sigint_external_command(int signum);
void		handle_sigint_heredoc(int signum);
char		*find_executable_path(char *command);
char		**prepare_args(char *executable_path, char **original_args);
int			handle_heredoc_redirection(t_command *cmd);
int			handle_file_input_redirection(t_command *cmd);
int			handle_input_redirection(t_command *cmd);
int			handle_output_redirection(t_command **command);
char		*expand_variables(char *str);
char		*remove_quotes(const char *str);
void		ft_echo(char **args);
void		ft_pwd(void);
void		ft_cd(char **args);
void		ft_export(char **args);

#endif
