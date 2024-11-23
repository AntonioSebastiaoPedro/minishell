# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    TestsCommands.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ateca <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 08:35:54 by ateca             #+#    #+#              #
#    Updated: 2024/11/19 17:47:29 by ateca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

1. Redirecionamento de Saída (>)
Esse redirecionamento cria um arquivo novo ou substitui o conteúdo de um arquivo existente com a saída do comando.

echo "Hello, World!" > output.txt       # Escreve "Hello, World!" em output.txt
ls -l > file_list.txt                    # Guarda a saída do comando ls -l em file_list.txt
date > current_date.txt                  # Guarda a data e hora actual em current_date.txt
////////////////////////////////////////////////////////////////////////////////

2. Redirecionamento de Entrada (<)
Usado para fornecer o conteúdo de um arquivo como entrada para um comando.

cat < output.txt                         # Lê e exibe o conteúdo de output.txt
sort < file_list.txt                     # Ordena o conteúdo de file_list.txt e exibe no terminal
grep "World" < output.txt                # Procura pela palavra "World" no arquivo output.txt
////////////////////////////////////////////////////////////////////////////////

3. Append (>>)
Esse redirecionamento adiciona conteúdo ao final do arquivo, em vez de substituí-lo.
echo "Adding a new line" >> output.txt   # Adiciona "Adding a new line" ao final de output.txt
echo "Another line" >> output.txt        # Adiciona "Another line" ao final de output.txt
ls >> file_list.txt                      # Adiciona a listagem de arquivos ao final de file_list.txt
////////////////////////////////////////////////////////////////////////////////

4. HEREDOC (<<)
Esse redirecionamento permite que você forneça múltiplas linhas de entrada para um comando até que ele encontre uma palavra específica (conhecida como delimitador).
cat << END                               # O comando lê até encontrar a palavra END
Hello,
This is a HEREDOC example.
END

Esse último comando cria um arquivo heredoc_output.txt com o conteúdo entre EOF e EOF.
cat << EOF > heredoc_output.txt
This is a test of HEREDOC with output redirection.
EOF

cat > zona.txt
////////////////////////////////////////////////////////////////////////////////

Exemplos de Heredoc (<<) com Comandos Externos
1.Usando grep para buscar texto especificado em várias linhas de entrada:
grep "Hello" << END
Hello, World!
Goodbye, World!
Hello again!
END

2.Usando sort para classificar linhas de entrada:
sort << END
banana
apple
orange
END

3.Usando wc para contar palavras, linhas ou caracteres:
O comando wc -w conta o número total de palavras nas linhas fornecidas.
wc -w << END
This is a test text.
Another line here.
END

4.Usando awk para processamento de texto:
Esse comando converte cada linha para maiúsculas, retornando.
awk '{ print toupper($0) }' << END
hello
world
END

5.Usando sed para substituir padrões de texto:
Esse comando substitui "World" por "Everyone", resultando em.
sed 's/World/Everyone/' << END
Hello World
Goodbye World
END

6.Usando rev para inverter o texto em cada linha:
rev << END
Hello
World
END
////////////////////////////////////////////////////////////////////////

1. Comandos Simples com Pipes

    Listar arquivos e contar: ls | wc -l
    Procurar uma palavra em um arquivo e contar: grep "palavra" arquivo.txt | wc -l
    Ordenar e remover duplicatas: cat arquivo.txt | sort | uniq

2. Sequência de Pipes

    Contar arquivos e somar linhas: ls -l | wc -l | xargs echo "Total files:"
    Filtrar e contar palavras: echo "teste" | grep "te" | wc -l
    Filtrar e extrair colunas: ps aux | grep root | awk '{print $1, $2}'

3. Testes de Erro e Saída Condicional

    Comando inexistente: ls -l | command_not_found | wc -l
    Filtro vazio: ls | grep "inexistente" | wc -l
    Saída redirecionada para erro: ls /diretorio_inexistente | grep "algo" | wc -l

4. Redirecionamento com Pipes

    Saída para arquivo: ls | tee arquivo.txt | wc -l
    Saída padrão e erro para o mesmo pipe: find / -name "arquivo_inexistente" 2>&1 | grep "Permission"

5. Comandos de Sistema e Variáveis de Ambiente

    Verificar variáveis de ambiente e filtro: env | grep PATH
    Comando em subshell: echo $(ls | wc -l) | cat
    Comando com várias pipelines: ls -l | grep "^d" | awk '{print $9}'

6. Combinações com Pipes e Heredoc (<<)

    Simulação com heredoc:

cat << EOF | grep "teste"
linha1
teste
linha3
EOF

echo "Hello, World!" | cat
ls | wc -l
who | grep "teca"

ls | wc -l > output.txt
cat output.txt

ls | comando_invalido

| ls
ls |

ls | grep "minishell" | wc -l

echo "42" | cat | grep "4"
who | sort | uniq | wc -l

////////////////////////////////////////////////////////////////////////////////
echo e" "f
echo tete"tete"
echo "teste"tete
echo "ccc"fff'hhhh'""ddd


