# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 14:00:58 by dhyun             #+#    #+#              #
#    Updated: 2022/09/30 01:00:46 by dhyun            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include

INC_LIB	= -L$(LIBFT_DIR) -lft -lreadline -L/opt/homebrew/opt/readline/lib

RM	= rm -f

HEADERS = minishell.h

SRCS	= ft_cd.c ft_cd_util.c ft_check_syntax.c ft_echo.c ft_exec.c\
		ft_exec_b_in.c ft_exec_cmds.c ft_exec_convert.c ft_exec_n_b_in.c\
		ft_exec_path.c ft_exec_utils.c ft_exit.c ft_init.c ft_make_command.c\
		ft_new_node.c ft_parse.c ft_parse_env.c ft_parse_push.c \
		ft_parse_util.c ft_pwd.c ft_re_dir.c ft_re_dir_util.c ft_set_env.c\
		ft_start_minishell.c ft_util.c get_next_line.c get_next_line_utils.c\
		main.c util1_export_env.c util2_unset.c\

OBJS	= $(SRCS:.c=.o)

LIBFT_DIR	= ./libft
LIBFT	= libft.a

NAME	= minishell

all:	$(LIBFT) $(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $@ $^ $(INC_LIB)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS):	$(HEADERS)

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(LIBFT_DIR)/$(LIBFT)
	$(RM) $(NAME)

re:
	make fclean
	make all

norm:
	norminette

.PHONY: all bonus clean fclean re norm libft.a
