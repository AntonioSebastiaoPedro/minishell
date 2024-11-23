# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 11:44:28 by ateca             #+#    #+#              #
#    Updated: 2024/11/22 14:34:35 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = builtins_utils.c echo.c env_utils3.c execute_external_command.c export.c handle_redirection.c minishell.c pwd.c token_utils.c \
	cd.c env.c  env_utils.c  exit.c find_path_prepare_args.c handle_signal.c  parser.c unset.c command_utils.c handle_output_redirection.c \
	env_utils2.c execute_commands.c expand_variables.c handle_input_redirection.c  print_utils.c tokenize.c handle_word.c

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
