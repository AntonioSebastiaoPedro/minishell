# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 11:44:28 by ateca             #+#    #+#              #
#    Updated: 2024/11/18 01:47:09 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = builtins_utils.c command_utils.c env.c export.c print_utils.c signal_hnadlers.c token_utils.c vars_utils.c \
	cd.c echo.c  env_utils.c minishell.c parser.c  pwd.c tokenize.c unset.c env_utils2.c exit.c execute_commands.c \
	heredoc_utils.c redirection_utils.c env_utils3.c

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
