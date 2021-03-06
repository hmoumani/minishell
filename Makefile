# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 10:53:07 by ojoubout          #+#    #+#              #
#    Updated: 2021/01/13 11:07:08 by ojoubout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRC = srcs/minishell.c srcs/handle_quotes.c srcs/handle_cmd.c srcs/handle_sig.c \
	srcs/redirect.c srcs/handle_exec.c srcs/handle_exec2.c srcs/env_var.c srcs/exec/ft_cd.c srcs/exec/ft_echo.c \
	srcs/exec/ft_export.c srcs/exec/ft_pwd.c srcs/exec/ft_unset.c \
	srcs/exec/ft_env.c srcs/exec/ft_exit.c srcs/exec/ft_export_outil.c srcs/exec/ft_export_outil1.c \
	srcs/utils.c srcs/utils2.c srcs/prompt.c srcs/parse.c srcs/env.c srcs/command.c srcs/utils3.c
SRC += gnl/get_next_line.c

OBJ = $(SRC:.c=.o)

FLAGS=-Wall -Wextra -Werror

all: $(NAME)

CC=gcc

$(NAME):
	@make CC=$(CC) -C libft bonus
	@$(CC) $(FLAGS) $(SRC) libft/libft.a -Iincludes -o $(NAME)

clean:
	@make -C libft clean


fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: fclean clean all re
