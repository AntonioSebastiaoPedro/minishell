/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:33:21 by ateca             #+#    #+#             */
/*   Updated: 2024/10/25 17:33:23 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_command
{
	char				*command;	// O comando principal (ex: "echo")
	char				**args;	// Argumentos do comando
	char				*input_redir;	// Redirecionador de entrada (ex: "< arquivo")
	char				*output_redir;	// Redirecionador de saída (ex: "> arquivo")
	int					append;	// Flag para redirecionamento em modo append (">>")
	struct s_command	*next;	// Próximo comando na lista
}		t_command;

// Função para verificar se um token é um comando
int	is_command(const char *token)
{
	return (token != NULL && !isdigit(token[0]) && strcmp(token, "|") != 0
		&& strcmp(token, "<") != 0 && strcmp(token, ">") != 0
		&& strcmp(token, ">>") != 0 && strcmp(token, "<<") != 0);
}

// Função para adicionar um novo comando à lista de comandos
t_command	*add_command(t_command **commands, const char *command)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
	{
		perror("malloc");
		return (NULL);
	}
	new_command->command = strdup(command);
	new_command->args = NULL; // Inicializa os argumentos como NULL
	new_command->input_redir = NULL;
	new_command->output_redir = NULL;
	new_command->append = 0; // Inicializa como 0
	new_command->next = *commands;
	*commands = new_command;
	return (new_command);
}

// Função para verificar se um token é um redirecionador
int	is_redirection(const char *token)
{
	return (strcmp(token, ">") == 0 || strcmp(token, "<") == 0
		|| strcmp(token, ">>") == 0 || strcmp(token, "<<") == 0);
}

// Função para manipular redirecionamentos
void	handle_redirection(t_token *token, t_command *current_cmd)
{
	if (strcmp(token->value, ">") == 0)
		current_cmd->output_redir = token->next->value;
	else if (strcmp(token->value, "<") == 0)
		current_cmd->input_redir = token->next->value;
	else if (strcmp(token->value, ">>") == 0)
	{
		current_cmd->output_redir = token->next->value;
		current_cmd->append = 1; // Marca como append
	}
	else if (strcmp(token->value, "<<") == 0)
		current_cmd->input_redir = token->next->value; // Aqui você pode lidar com redirecionamento de HEREDOC se necessário
}

// Função para verificar se um token é um argumento
int	is_argument(const char *token)
{
	return (token != NULL && !is_redirection(token) && strcmp(token, "|") != 0);
}

// Função para adicionar argumento ao comando atual
void	add_argument(t_command *cmd, const char *arg)
{
	int	count;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
		{
			count++;
		}
	}
	cmd->args = realloc(cmd->args, sizeof(char *) * (count + 2)); // +1 para o novo argumento, +1 para NULL
	cmd->args[count] = strdup(arg);
	cmd->args[count + 1] = NULL; // Adiciona o NULL no final
}

// Função para analisar tokens e construir a lista de comandos
t_command	*parse_tokens(t_token *tokens)
{
	t_command	*commands;
	t_command	*current_cmd;

	commands = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (is_command(tokens->value))
			current_cmd = add_command(&commands, tokens->value);
		else if (is_redirection(tokens->value))
			handle_redirection(tokens, current_cmd);
		else if (is_argument(tokens->value))
			add_argument(current_cmd, tokens->value);
		tokens = tokens->next;
	}
	return (commands);
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
			break; // Ctrl-D
		add_history(line);
		// Tokeniza a linha de entrada
		tokens = tokenize(line);
		// Analisa os tokens para construir a lista de comandos
		commands = parse_tokens(tokens);
		// Aqui você poderia executar os comandos
		// execute_commands(commands);
		// Libere a memória alocada (tokens e comandos)
		// free_tokens(tokens);
		// free_commands(commands);
	}
	return (0);
}
