/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:19:19 by ateca             #+#    #+#             */
/*   Updated: 2024/11/05 07:37:08 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t g_child_pid = 0;

void	free_commands(t_command *commands)
{
	int			i;
	t_command	*current;
	t_command	*next;

	if (commands == NULL)
		return ;
	current = commands;
	while (current)
	{
		next = current->next;
		free(current->command);
		if (current->args)
		{
			i = -1;
			while (current->args[++i] != NULL)
				free(current->args[i]);
			free(current->args);
		}
		free(current);
		current = next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (tokens == NULL)
		return ;
	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	print_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		printf("Token: %s\n", temp->value);
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

void	exec_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->command, "echo") == 0)
		ft_echo(cmd->args);
	else if (ft_strcmp(cmd->command, "cd") == 0)
		ft_cd(cmd->args);
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->command, "exit") == 0)
		exit(0);
}

int	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0);
}

void	extract_variable_name(const char *str, int *i, char *var_name)
{
	int	j;

	j = 0;
	(*i)++;
	while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
		var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
}

char	*expand_variables(const char *str)
{
	int			pos;
	int			i;
	char		*env_val;
	char		*result;
	char		var_name[1024];

	result = malloc(sizeof(char) * 1024);
	pos = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			extract_variable_name(str, &i, var_name);
			env_val = getenv(var_name);
			if (env_val)
			{
				strcpy(result + pos, env_val);
				pos += strlen(env_val);
			}
		}
		else
			result[pos++] = str[i++];
	}
	result[pos] = '\0';
	return (result);
}

int	copy_arguments(char **args, t_command *next_cmd)
{
	int	i;
	int	count;
	
	count = 0;
	while (args && args[count])
		count++;
	next_cmd->args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!next_cmd->args)
	{
		perror("minishell: malloc failed");
		return (-2);
	}
	i = 0;
	while (i < count)
	{
		next_cmd->args[i] = ft_strdup(args[i]);
		i++;
	}
	next_cmd->args[count] = NULL;
	return (0);
}


int	handle_output_redirection(t_command **command)
{
	int		flags;
	int		status;
	int		fd_write;
	t_command	*cmd;

	status = 0;
	cmd = *command;
	flags = O_WRONLY | O_CREAT;
	if (cmd->write_pipe_fd > 0)
		close(cmd->write_pipe_fd);
	while (cmd && cmd->output_redir)
	{
		if (cmd->append == 1)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd_write = open(cmd->output_redir, flags, 0644);
		if (fd_write < 0)
		{
			printf("minishell: %s: %s\n", cmd->output_redir, strerror(errno));
			return (-2);
		}
		if (cmd->next && cmd->next->output_redir)
		{
			close(fd_write);
			if (cmd->command != NULL && ft_strcmp(cmd->command, "echo") == 0)
			{
				cmd->next->command = ft_strdup(cmd->command);
				status = copy_arguments(cmd->args, cmd->next);
				if (status == -2)
					break ;
			}
			else if (cmd->read_pipe_fd > 0)
				cmd->next->read_pipe_fd = cmd->read_pipe_fd;
			cmd = cmd->next;
		}
		else
		{
			if (cmd->read_pipe_fd > 0)
				cmd->command = ft_strdup("cat");
			dup2(fd_write, STDOUT_FILENO);
			close(fd_write);
			*command = cmd;
			break ;
		}
	}
	return (status);
}

void	handle_sigint_heredoc(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

void	handle_heredoc(t_command *cmd)
{
	int		write_check;
	char	*line;
	char	*delimiter;
	
	write_check = 0;
	delimiter = cmd->input_redir;
	signal(SIGINT, handle_sigint_heredoc);
	close(cmd->read_pipe_fd);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			if (write_check == 0)
				exit(0);
			break ;
		}
		write_check = 1;
		write(cmd->write_pipe_fd, line, strlen(line));
		write(cmd->write_pipe_fd, "\n", 1);
		free(line);
	}
	close(cmd->write_pipe_fd);
	exit(0);
}

int	handle_input_redirection(t_command *cmd)
{
	int		fd;
	int		status;
	pid_t	pid;

	if (cmd->heredoc)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			handle_heredoc(cmd);
		else if (pid < 0)
		{
			signal(SIGINT, handle_sigint);
			perror("minishell: fork failed");
			return (-2);
		}
		else
		{
			close(cmd->write_pipe_fd);
			dup2(cmd->read_pipe_fd, STDIN_FILENO);
			close(cmd->read_pipe_fd);
			waitpid(pid, &status, 0);
			cmd->write_pipe_fd = -1;
			cmd->read_pipe_fd = -1;
			signal(SIGINT, handle_sigint);
			if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 0)
			{
				if (cmd->next != NULL)
					return (-3);
				return (0);
			}
			else
				return (-2);
		}
	}
	else
	{
		fd = open(cmd->input_redir, O_RDONLY);
		if (fd < 0)
		{
			printf("minishell: %s: %s\n",  cmd->input_redir, strerror(errno));
			return (-2);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	handle_redirections(t_command **cmd)
{
	if ((*cmd)->input_redir != NULL)
		return (handle_input_redirection(*cmd));
	else if ((*cmd)->output_redir != NULL)
		return (handle_output_redirection(cmd));
	return (0);
}

char	**prepare_args(char *executable_path, char **original_args)
{
	int		i;
	int		arg_count;
	char	**new_args;

	arg_count = 0;
	while (original_args && original_args[arg_count])
		arg_count++;
	new_args = malloc((arg_count + 2) * sizeof(char *));
	if (!new_args)
	{
		perror("minishell: malloc failed");
		exit(1);
	}
	new_args[0] = ft_strdup(executable_path);
	if (!new_args[0])
	{
		perror("minishell: malloc failed");
		free(new_args);
		exit(1);
	}
	i = -1;
	while (++i < arg_count)
		new_args[i + 1] = original_args[i];
	new_args[arg_count + 1] = NULL;
	return (new_args);
}

char	*absolute_relative_path(char *command)
{
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	else
	{
		printf("minishell: %s: %s\n", strerror(errno), command);
		exit(1);
	}
}

char	*find_executable_path(char *command)
{
	char	*dir;
	char	*path;
	char	*path_copy;
	char	*next_path;
	char	*exec_path;

	if (strchr(command, '/') != NULL)
		return (absolute_relative_path(command));
	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	dir = ft_strtok(path_copy, ':', &next_path);
	while (dir)
	{
		exec_path = ft_strjoin_delimiter(dir, '/', command);
		if (access(exec_path, F_OK) == 0 && access(exec_path, X_OK) == 0)
		{
			free(path_copy);
			return (exec_path);
		}
		dir = ft_strtok(NULL, ':', &next_path);
	}
	free(path_copy);
	return (NULL);
}

void	handle_sigint_external_command(int signum)
{
	(void)signum;
	if (g_child_pid > 0)
	{
		write(STDERR_FILENO, "\n", 1);
		kill(g_child_pid, SIGINT);
	}
}

void	execute_external_command(t_command *cmd, char **envp)
{
	char	**new_args;
	char	*executable_path;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_sigint_external_command);
	pid = fork();
	if (pid == 0)
	{
		if (cmd->write_pipe_fd != -1)
		{
			dprintf(2, "write_pipe_fd: %d\n", cmd->write_pipe_fd);
			dup2(cmd->write_pipe_fd, STDOUT_FILENO);
			close(cmd->write_pipe_fd);
		}
		if (cmd->read_pipe_fd != -1)
		{
			dprintf(2, "read_pipe_fd: %d\n", cmd->read_pipe_fd);
			dup2(cmd->read_pipe_fd, STDIN_FILENO);
			close(cmd->read_pipe_fd);
		}
		executable_path = find_executable_path(cmd->command);
		if (!executable_path)
		{
			printf("minishell: command not found: %s\n", cmd->command);
			exit(127);
		}
		new_args = prepare_args(executable_path, cmd->args);
		if (!new_args)
		{
			perror("minishell: prepare_args failed");
			exit(1);
		}
		execve(executable_path, new_args, envp);
		free(executable_path);
		perror("minishell");
		exit(errno);
	}
	else if (pid < 0)
		perror("minishell: fork failed");
	else
	{
		g_child_pid = pid;
		waitpid(pid, NULL, 0);
		g_child_pid = 0;
		if (cmd->read_pipe_fd != -1)
			close(cmd->read_pipe_fd);
		if (cmd->write_pipe_fd != -1)
			close(cmd->write_pipe_fd);
		signal(SIGINT, handle_sigint);
	}
}

void	execute_commands(t_command *cmd, char **envp)
{
	int	i;
	int	result;
	int	pipe_fd[2];
	int	original_stdin;
	int	original_stdout;
	
	result = 0;
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	while (cmd != NULL)
	{
		if (cmd->next != NULL 
			|| (cmd->command && cmd->input_redir && cmd->heredoc))
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("minishell: pipe failed");
				break ;
			}
		}
		if (cmd->next != NULL)
		{
			cmd->write_pipe_fd = pipe_fd[1];
			cmd->next->read_pipe_fd = pipe_fd[0];
		}
		else if (cmd->command && cmd->input_redir && cmd->heredoc)
		{
			cmd->write_pipe_fd = pipe_fd[1];
			cmd->read_pipe_fd = pipe_fd[0];
		}
		i = -1;
		if (cmd->args)
		{
			while (cmd->args[++i])
				cmd->args[i] = expand_variables(cmd->args[i]);
		}
		result = handle_redirections(&cmd);
		if (result == -2)
			break ;
		else if (result == -3)
		{
			cmd = cmd->next;
			continue ;
		}
		if (cmd->command != NULL && is_builtin(cmd->command))
			exec_builtin(cmd);
		else
		{
			execute_external_command(cmd, envp);
		}
		cmd = cmd->next;
	}
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

int	main(int argc, char *argv[], char **envp)
{
	char		*line;
	t_token		*tokens;
	t_command	*commands;

	(void) argc;
	(void) argv;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{	
		tokens = NULL;
		line = readline("ansebastian@ateca-Akastuki:~/minishell$ ");
		//line = readline("\033[1m\033[33mansebastian@ateca\033[0m-\033[1m\033[35mAkatsuki\033[0m:\033[1m\033[36m~/minishell\033[0m$ ");
		if (!line)
			break ;
		add_history(line);
		tokenize(line, &tokens);
		commands = parse_tokens(tokens);
		//print_tokens(tokens);
		//print_commands(commands);
		execute_commands(commands, envp);
		free(line);
		free_tokens(tokens);
		free_commands(commands);
	}
	rl_clear_history();
	return (0);
}
