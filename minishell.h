/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:25:08 by ateca             #+#    #+#             */
/*   Updated: 2024/11/18 04:23:06 by ansebast         ###   ########.fr       */
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

typedef struct s_command
{
	char				*command;
	char				**args;
	char				*input_redir;
	char				*output_redir;
	int					append;
	int					*interpret;
	int					heredoc;
	struct s_command	*next;
}						t_command;

extern volatile sig_atomic_t g_heredoc_interrupted;

int						ft_env(t_command *cmd, t_env **env);
int						is_builtin(const char *cmd);
int						is_command(const char *token);
void					tokenize(char *line, t_token **tokens);
void					ft_echo(char **args);
void					ft_pwd(void);
void					ft_cd(char **args, t_env **env);
void					ft_export(t_command *cmd, t_env **env);
void					free_env(t_env **env);
void					exec_builtin(t_command *cmd, t_env **env);
void					handle_sigint(int sig);
void					handle_sigquit(int sig);
void					exec_builtin(t_command *cmd, t_env **env);
void					execute_commands(t_command *cmd, t_env **env);
void					free_commands(t_command *commands);
void					envcpy(t_env **env_dup, char **src);
void					print_tokens(t_token *tokens);
void					print_commands(t_command *commands);
void					free_tokens(t_token *tokens);
void					add_back(t_env **head, t_env *new_env);
void					ft_unset(t_command *cmd, t_env **env);
void					ft_exit(t_command *cmd);
void					extract_variable_name(const char *str, int *i,
							char *var_name);
void					update_env(t_env **env, char *name);
char					*expand_variables(const char *str, t_command *cmd,
							int *arg_pos, t_env **env);
t_env					*add_env(t_env **envs, char *name);
t_token					*add_token(t_token *head, char *value, int interpret);
t_command				*parse_tokens(t_token *tokens);
t_command				*add_command(t_command **commands, const char *command);
t_env					*ft_newenv(char *name);
t_env					*last_env(t_env *head);
t_env					*get_env(char *var, t_env **env, int (*cmp)());
char					*get_env_value(char *var, t_env **env);
int					handle_redirections(t_command *cmd);
int					handle_heredoc(char *delimiter);
char					**env_list_to_array(t_env *env_list);
void					update_shlvl(t_env **env);
void					update_envvar(t_env **env, char *var, char *value);

#endif
