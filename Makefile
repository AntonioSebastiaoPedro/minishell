# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 11:44:28 by ateca             #+#    #+#              #
#    Updated: 2024/11/05 01:42:23 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./minishell.c ./tokenize.c ./add_token.c ./parser.c ./echo.c ./pwd.c ./cd.c \
       ./execute_commands.c ./execute_external_command.c ./find_path_prepare_args.c \
       ./handle_input_redirection.c ./handle_output_redirection.c ./expand_variables.c \
       ./handle_signal.c ./minishell_utils.c

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
