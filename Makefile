# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 10:53:07 by ojoubout          #+#    #+#              #
#    Updated: 2019/11/23 22:10:50 by ojoubout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRC = srcs/minishell.c srcs/ft_sh_split.c srcs/handle_cmd.c srcs/handle_sig.c \
	srcs/redirect.c srcs/handle_exec.c srcs/exec/ft_cd.c srcs/exec/ft_echo.c \
	srcs/exec/ft_export.c srcs/exec/ft_pwd.c srcs/exec/ft_unset.c \
	srcs/exec/ft_env.c srcs/exec/ft_exit.c
SRC += gnl/get_next_line.c

OBJ = $(SRC:.c=.o)

FLAGS=-Wall -Wextra -Werror -fsanitize=address -g

all: $(NAME)

$(NAME):
	@make -C libft bonus
	@make -C ft_printf all
	@gcc $(FLAGS) $(SRC) libft/libft.a ft_printf/libftprintf.a -Iincludes -o $(NAME)

clean:
	@make -C libft clean
	@make -C ft_printf clean


fclean: clean
	@make -C libft fclean
	@make -C ft_printf fclean

	@rm -rf $(NAME)

re: fclean all

.PHONY: fclean clean all re
