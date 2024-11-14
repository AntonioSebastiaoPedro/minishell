# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    TestsCommands                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ateca <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 08:35:54 by ateca             #+#    #+#              #
#    Updated: 2024/11/13 08:35:59 by ateca            ###   ########.fr        #
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

