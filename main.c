#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\nminishell> ", 12);
}

void	execute_command(char **args, char **envp)
{
	if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] != NULL)
			chdir(args[1]);
		else
			printf("cd: missing argument\n");
	} 
	else if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
	} 
	else if (strcmp(args[0], "pwd") == 0)
	{
		char *pwd = getcwd(NULL, 0);
		if (pwd)
		{
			printf("%s\n", pwd);
			free(pwd);
		}
	} 
	else
	{
		execve("/bin/ls", args, envp);
		perror("execve");  // Exibe erro se o comando não foi encontrado
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*args[10]; // Suporte a até 10 argumentos para simplificação

	signal(SIGINT, sig_handler);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break; // Ctrl-D
		add_history(line);

		// Tokenização simples da linha para simular vários argumentos
		int i = 0;
		char *token = strtok(line, " ");
		while (token != NULL && i < 10)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		execute_command(args, envp);
		free(line);
	}
	return (0);
}

