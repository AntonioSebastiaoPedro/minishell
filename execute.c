/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:08:31 by ateca             #+#    #+#             */
/*   Updated: 2024/10/26 16:08:33 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Tratamento de pipes
void	handle_pipes(t_command *cmd)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		execute_commands(cmd);
	}
	else if (pid > 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		perror("fork failed");
		exit(1);
	}
}

// Tratamento de redirecionamento
void	handle_redirection(t_command *cmd)
{
	int	fd;

	if (cmd->input_redir)
	{
		fd = open(cmd->input_redir, O_RDONLY);
		if (fd < 0)
		{
			perror("input redirection failed");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->output_redir)
	{
		fd = open(cmd->output_redir, O_WRONLY | O_CREAT | (cmd->append ? O_APPEND : O_TRUNC), 0644);
		if (fd < 0)
		{
			perror("output redirection failed");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

// Executa comandos built-in
void	exec_builtin(t_command *cmd)
{
	int	i;

	if (strcmp(cmd->command, "echo") == 0)
	{	
		if (strcmp(cmd->args[1], "-n") == 0)
			i = 2;
		else
			i = 1;
		while (cmd->args[i++])
		{
			printf("%s", cmd->args[i]);
			if (cmd->args[i + 1])
				printf(" ");
		}
		if (strcmp(cmd->args[1], "-n") != 0)
			printf("\n");
	}
	else if (strcmp(cmd->name, "cd") == 0)
	{
		if (chdir(cmd->args[1]) != 0)
			perror("cd failed");
	}
	else if (strcmp(cmd->name, "pwd") == 0)
	{
		char	cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		else
			perror("pwd failed");
	}
	else if (strcmp(cmd->name, "exit") == 0)
		exit(0);
}

// Verifica se é um built-in
int	is_builtin(const char *cmd)
{
    return (strcmp(cmd, "echo") == 0 || strcmp(cmd, "cd") == 0 || strcmp(cmd, "pwd") == 0 || strcmp(cmd, "exit") == 0);
}

// Tratamento de citações
char	*handle_quotes(const char *str)
{
	char	*new_str;
	size_t	len;

	new_str = strdup(str);
	if (str[0] == '\'' || str[0] == '"')
	{
		len = strlen(new_str);
		if (new_str[len - 1] == str[0])
		{
			new_str[len - 1] = '\0';
			new_str++;
		}
	}
	return (new_str);
}

// Expansão de variáveis
char	*expand_variables(const char *str)
{
	const char	*env_val;

	if (str[0] == '$')
	{
		env_val = getenv(str + 1);
		if (env_val)
			return (strdup(env_val));
		else
			return (strdup(""));
	}
	return (strdup(str));
}

// Função principal de execução
void	execute_commands(t_command *cmd)
{
	int		i;
	pid_t	pid;

	while (cmd)
	{
		i = -1;
		while (cmd->args[++i]) // Expande variáveis e trata citações
			cmd->args[i] = expand_variables(handle_quotes(cmd->args[i]));
		if (is_builtin(cmd->command)) // Executa comandos internos (built-ins)
			exec_builtin(cmd);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				handle_redirection(cmd);
				execve(cmd->command, cmd->args, environ); // Executa o comando externo
				perror("execve failed");
				exit(1);
			}
			else if (pid < 0)
				perror("fork failed");
			else
				waitpid(pid, NULL, 0); // Espera pelo processo filho
		}
	}
	cmd = cmd->next;
}

// Função para executar comandos
void	execute_commands(t_command *cmd)
{
    int pipefd[2]; // Array para armazenar os descritores do pipe
    pid_t pid;
    
    while (cmd) {
        // Expande variáveis e trata citações
        for (int i = 0; cmd->args[i]; i++)
            cmd->args[i] = expand_variables(handle_quotes(cmd->args[i]));
        
        // Se houver um comando seguinte, cria um pipe
        if (cmd->next) {
            if (pipe(pipefd) == -1) {
                perror("pipe failed");
                exit(1);
            }
        }

        // Executa comandos internos (built-ins)
        if (is_builtin(cmd->command)) {
            exec_builtin(cmd);
        } else {
            pid = fork();
            if (pid == 0) {
                // Se houver um comando seguinte, redireciona a saída para o pipe
                if (cmd->next) {
                    dup2(pipefd[1], STDOUT_FILENO); // Redireciona stdout para o pipe
                    close(pipefd[0]); // Fecha o lado de leitura do pipe no filho
                    close(pipefd[1]); // Fecha o lado de escrita do pipe após duplicar
                }

                handle_redirection(cmd);
                execve(cmd->command, cmd->args, environ); // Executa o comando externo
                perror("execve failed");
                exit(1);
            } else if (pid < 0) {
                perror("fork failed");
            } else {
                if (cmd->next) {
                    close(pipefd[1]); // Fecha o lado de escrita do pipe no pai
                    dup2(pipefd[0], STDIN_FILENO); // Redireciona stdin para o pipe
                    close(pipefd[0]); // Fecha o lado de leitura do pipe após duplicar
                }
                waitpid(pid, NULL, 0); // Espera pelo processo filho
            }
        }
        cmd = cmd->next; // Passa para o próximo comando
    }
}


int	main(void)
{
	char		line[1024];
	t_token		*tokens;
	t_command	*commands;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		add_history(line);
		// Tokeniza a linha de entrada
		tokens = tokenize(line);
		// Analisa os tokens para construir a lista de comandos
		commands = parse_tokens(tokens);
		// Aqui você poderia executar os comandos
		// execute_commands(commands);
		// Libere a memória alocada (tokens e comandos)
		free(line);
		// free_tokens(tokens);
		// free_commands(commands);
	}
	return (0);
}
