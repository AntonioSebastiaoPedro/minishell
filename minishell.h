/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:25:08 by ateca             #+#    #+#             */
/*   Updated: 2024/11/28 15:18:48 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_token
{
	char				*value;
	int					interpret;
	struct s_token		*next;
}						t_token;

typedef struct s_env
{
	char				*var;
	char				*value;
	int					index;
	int					show;
	struct s_env		*next;
}						t_env;

typedef struct s_quote_state
{
	int	dob_quote;
	int	sin_quote;
	int	interpret;
}					t_quote_state;

typedef struct s_expand_state
{
	char	*result;
	int		pos;
	t_env	**env;
}					t_expand_state;

typedef struct s_command
{
	char				*command;
	char				**args;
	char				*input_redir;
	char				*output_redir;
	int					append;
	int					*interpret;
	int					heredoc;
	int					invalid_redir;
	int					write_pipe_fd;
	int					read_pipe_fd;
	struct s_command	*next;
}						t_command;

int			ft_env(t_command *cmd, t_env **env);
int			is_builtin(const char *cmd);
int			is_command(const char *token);
int			ft_echo(t_command *cmd);
int			ft_pwd(void);
int			ft_cd(char **args, t_env **env);
int			ft_export(t_command *cmd, t_env **env);
int			exec_builtin(t_command *cmd, int original_stdout, t_env **env);
int			ft_unset(t_command *cmd, t_env **env);
int			ft_exit(t_command *cmd);
int			handle_redirections(t_command **cmd, int fd_stdout);
int			is_redirection(const char *token);
int			execute_external_command(t_command *cmd, t_env **envp);
int			expects_stdin(char *cmd);
int			check_isspace(char *line, int i);
int			handle_input_redirection(t_command *cmd, int fd_stdout);
int			handle_output_redirection(t_command **command);
int			is_argument(const char *token);
void		handle_heredoc(t_command *cmd);
void		free_env(t_env **env);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		tokenize(char *line, t_token **tokens);
void		execute_commands(t_command *cmd, t_env **env);
void		free_commands(t_command *commands);
void		envcpy(t_env **env_dup, char **src);
void		print_tokens(t_token *tokens);
void		print_commands(t_command *commands);
void		free_tokens(t_token *tokens);
void		add_back(t_env **head, t_env *new_env);
void		extract_variable_name(const char *str, int *i, char *var_name);
void		update_env(t_env **env, char *name);
void		update_shlvl(t_env **env);
void		update_envvar(t_env **env, char *var, char *value);
void		print_error_redirection_single(char *redir);
void		handle_redirection(t_token *token, t_command *current_cmd);
void		add_argument(t_command *cmd, t_token *token);
void		print_error_redirection_file(char *file_redir);
void		handle_word(const char *line, int *i, t_token **tokens);
void		handle_sigint_external_command(int signum);
void		handle_sigint_heredoc(int signum);
void		handle_pipe_stdin(char *line, t_token **tokens, int *i);
char		*expand_variables(char *str, t_command *cmd, int *arg_pos,
				t_env **env);
char		*get_env_value(char *var, t_env **env);
char		**env_list_to_array(t_env *env_list);
char		*find_executable_path(char *command, t_env **env);
char		**prepare_args(char *executable_path, char **original_args);
char		*realloc_token(char *buffer, int *capacity);
t_env		*add_env(t_env **envs, char *name);
t_env		*ft_newenv(char *name);
t_env		*last_env(t_env *head);
t_env		*get_env(char *var, t_env **env, int (*cmp)());
t_token		*add_token(t_token *head, char *value, int interpret);
t_command	*parse_tokens(t_token *tokens);
t_command	*add_command(t_command **commands, char *command);

#endif
