# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 11:44:28 by ateca             #+#    #+#              #
#    Updated: 2024/11/28 15:15:49 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = echo.c env_utils.c expand_variables.c handle_output_redirection.c handle_word.c print_utils.c unset.c \
	builtins_utils.c env.c execute_commands.c export.c handle_pipe_stdin.c minishell.c pwd.c \
	cd.c env_utils2.c execute_external_command.c find_path_prepare_args.c handle_redirection.c minishell_utils.c tokenize.c \
	command_utils.c env_utils3.c exit.c handle_input_redirection.c handle_signal.c parser.c token_utils.c \

LIBFT = $(LIBSRC)/libft.a
LIBSRC = ./libft

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g

OBJS = ${SRCS:.c=.o}

all:	${NAME}

$(NAME): $(OBJS) $(LIBFT)
	 @${CC} ${CFLAGS} ${OBJS} -L$(LIBSRC) -lft -I$(LIBSRC) -o $(NAME) -lreadline
	 @echo "\nCreated $(NAME) \n"
	 
$(LIBFT):
	@make -C $(LIBSRC)

clean:
	@${RM} ${OBJS}
	@make clean -C $(LIBSRC)
	@echo "\nAll objects cleaned successfully\n"

fclean: 
	@${RM} ${OBJS}
	@${RM} ${NAME}
	@make fclean -C $(LIBSRC)
	@echo "\nAll objects and executable cleaned successfully\n"
re: fclean all

.PHONY: all clean fclean re
