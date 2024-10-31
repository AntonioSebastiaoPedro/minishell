# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ateca <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 11:44:28 by ateca             #+#    #+#              #
#    Updated: 2024/10/30 11:44:30 by ateca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./minishell.c \
       ./tokenize.c \
       ./add_token.c \
       ./parser.c

INCLUDE = minishell.h

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

all:	${NAME}

$(NAME): $(OBJS) $(INCLUDE)
	 @${CC} ${CFLAGS} ${OBJS} -o $(NAME) -lreadline
	 @echo "\nCreated $(NAME) \n"

clean:
			@${RM} ${OBJS}
			@echo "\nAll objects cleaned successfully\n"

fclean: 
			@${RM} ${OBJS}
			@${RM} ${NAME}
			@echo "\nAll objects and executable cleaned successfully\n"
re: fclean all

.PHONY: all clean fclean re
