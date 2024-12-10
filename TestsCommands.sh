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

cat << END > output.txt

cat << END > output.txt > output1.txt > output2.txt

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

cat < file.txt | grep "42" > result.txt

ls > a << vc

////////////////////////////////////////////////////////////////////////////////
echo e" "f
echo tete"tete"
echo "teste"tete
echo "ccc"fff'hhhh'""ddd
///////////////////////////////////////////////////////////////////////////////

ateca@c1r2s4:~/minishell_ansebastian$ echo $1USER
USER
ateca@c1r2s4:~/minishell_ansebastian$ echo $1

ateca@c1r2s4:~/minishell_ansebastian$ $USER
Command 'ateca' not found, did you mean:
  command 'azteca' from snap azteca (1.0)
See 'snap info <snapname>' for additional versions.
ateca@c1r2s4:~/minishell_ansebastian$ echo "$USER""$USERNAME" | cat -e
ateca$
ateca@c1r2s4:~/minishell_ansebastian$ echo $USERNAME

ateca@c1r2s4:~/minishell_ansebastian$ echo "$USER""$USER" | cat -e
atecaateca$
ateca@c1r2s4:~/minishell_ansebastian$ echo "$USER teste""$USER" | cat -e
ateca testeateca$
ateca@c1r2s4:~/minishell_ansebastian$ echo "$USER-teste""$USER" | cat -e
ateca-testeateca$
ateca@c1r2s4:~/minishell_ansebastian$ echo s""s""
ss

Akatsuki> cat | cat | ls
Akatsuki> echo $
Akatsuki> ls ||
$PATH

Akatsuki> export USER="ls -l"
Akatsuki> $USER
$USER: command not found
Akatsuki> echo $USER
ls -l
Akatsuki>

ateca@c1r1s5:~/minishell_ansebastian$ e |
> ^C
ateca@c1r1s5:~/minishell_ansebastian$ < |
bash: syntax error near unexpected token `|'
ateca@c1r1s5:~/minishell_ansebastian$ > |
bash: syntax error near unexpected token `|'
ateca@c1r1s5:~/minishell_ansebastian$ >> |
bash: syntax error near unexpected token `|'
ateca@c1r1s5:~/minishell_ansebastian$ << |
bash: syntax error near unexpected token `|'
ateca@c1r1s5:~/minishell_ansebastian$ | |
bash: syntax error near unexpected token `|'
ateca@c1r1s5:~/minishell_ansebastian$ ||
bash: syntax error near unexpected token `||'
ateca@c1r1s5:~/minishell_ansebastian$
ateca@c1r2s4:~/minishell_ansebastian$ | ls | wc -l
bash: syntax error near unexpected token `|

char *test1 = "ls |";
	char *test2 = "echo Hello ||";
	char *test3 = "   pwd | ";
	char *test4 = "grep 'pattern' || ";
	char *test5 = "   ||"; // Inválido
	char *test6 = "ls || |"; // Inválido
	char *test7 = "<< |"; // Inválido
	char *test8 = ">> ||"; // Inválido
	char *test9 = "cat < ||"; // Inválido

ls '|'

ateca@c1r1s3:~/minishell_ansebastian$ cd ./qwewqe
bash: cd: ./qwewqe: No such file or directory
ateca@c1r1s3:~/minishell_ansebastian$ echo $?
1
ateca@c1r1s3:~/minishell_ansebastian$ ./minishell 
Akatsuki> cd ./weeewrewr
No such file or directory: Akatsuki> echo $?
 ?
Akatsuki> echo $?$?
 ?0
Akatsuki> 

ateca@c1r1s3:~/minishell_ansebastian$ echo $1;

ateca@c1r1s3:~/minishell_ansebastian$ echo $2;

ateca@c1r1s3:~/minishell_ansebastian$ echo $7;

ateca@c1r1s3:~/minishell_ansebastian$ echo $ 7;
$ 7
ateca@c1r1s3:~/minishell_ansebastian$ $1
ateca@c1r1s3:~/minishell_ansebastian$ $ 1
$: command not found
ateca@c1r1s3:~/minishell_ansebastian$ $1
ateca@c1r1s3:~/minishell_ansebastian$

ateca@c1r3s6:~/minishell_ansebastian$ ls > >>
bash: syntax error near unexpected token `>>'
ateca@c1r3s6:~/minishell_ansebastian$ ls > >
bash: syntax error near unexpected token `>
ateca@c1r3s6:~/minishell_ansebastian$ ls < <<
bash: syntax error near unexpected token `<<
ateca@c1r3s6:~/minishell_ansebastian$ ls < <
bash: syntax error near unexpected token `<
ateca@c1r3s6:~/minishell_ansebastian$ ls < >
bash: syntax error near unexpected token `>
ateca@c1r3s6:~/minishell_ansebastian$ ls < >>
bash: syntax error near unexpected token `>>
ateca@c1r3s6:~/minishell_ansebastian$ ls > <
bash: syntax error near unexpected token `<'
ateca@c1r3s6:~/minishell_ansebastian$ ls > <<
bash: syntax error near unexpected token `<<
ateca@c1r3s6:~/minishell_ansebastian$ ls >> <<
bash: syntax error near unexpected token `<<'

ateca@c1r2s4:~/minishell_ansebastian$ echo $$
18294
ateca@c1r2s4:~/minishell_ansebastian$ echo $?
0
ateca@c1r2s4:~/minishell_ansebastian$ echo $??
0?
ateca@c1r2s4:~/minishell_ansebastian$

ateca@c1r2s4:~/minishell_ansebastian$ echo $?
0
ateca@c1r2s4:~/minishell_ansebastian$ echo $??
0?
ateca@c1r2s4:~/minishell_ansebastian$ $?
0: command not found
ateca@c1r2s4:~/minishell_ansebastian$ $1?
?: command not found
ateca@c1r2s4:~/minishell_ansebastian$ 

ateca@c1r2s4:~/minishell_ansebastian$ echo "TEste Escola
> TEste Escola
> "
TEste Escola
TEste Escola

Akatsuki> export USER="ls -l"
Akatsuki> env
SYSTEMD_EXEC_PID=11650
SSH_AUTH_SOCK=/run/user/101267/keyring/ssh
SESSION_MANAGER=local/c1r2s4.42luanda.com:@/tmp/.ICE-unix/11650,unix/c1r2s4.42luanda.com:/tmp/.ICE-unix/11650
GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/1b6fc741_0472_480d_8d0c_699cfad8a1f0
LANG=en_US.UTF-8
XDG_CURRENT_DESKTOP=ubuntu:GNOME
PWD=/nfs/homes/ateca/minishell_ansebastian
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/ateca
LIBVIRT_DEFAULT_URI=qemu:///system
GPG_AGENT_INFO=/run/user/101267/gnupg/S.gpg-agent:0:1
DESKTOP_SESSION=ubuntu
QT_IM_MODULE=ibus
XDG_MENU_PREFIX=gnome-
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
USER=ls -l
XDG_CMD_STATUS=0
Akatsuki>

Akatsuki> export | wc -l >> a

ateca@c1r3s6:~/minishell_ansebastian$ > a ls -l
ateca@c1r3s6:~/minishell_ansebastian$ cat a



