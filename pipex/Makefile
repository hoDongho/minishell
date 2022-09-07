# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 14:00:58 by dhyun             #+#    #+#              #
#    Updated: 2022/07/17 20:39:00 by dhyun            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -I$(INCLUDE)

INC_LIB	= -L$(LIBFT_DIR) -lft

RM	= rm -f

INCLUDE	= ./include
HEADERS = $(INCLUDE)/pipex.h
HEADERS_BONUS = $(INCLUDE)/pipex_bonus.h

DIR_BONUS	= ./bonus

SRCS	= pipex.c init.c utils.c args.c exec.c option.c
SRCS_BONUS	= pipex_bonus.c init_bonus.c  utils_bonus.c\
			args_bonus.c exec_bonus.c option_bonus.c\
			here_doc_bonus.c

OBJS	= $(SRCS:.c=.o)
OBJS_BONUS	= $(addprefix $(DIR_BONUS)/, $(SRCS_BONUS:.c=.o))

LIBFT_DIR	= ./ft_lib
LIBFT	= libft.a

NAME	= pipex

ifdef WITH_BONUS
	OBJS = $(OBJS_BONUS)
else
	OBJS = $(SRCS:.c=.o)
endif

all:	$(LIBFT) $(NAME)

bonus:
	@make WITH_BONUS=1 all

$(NAME):	$(OBJS)
	$(CC) -o $@ $^ $(INC_LIB)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS):	$(HEADERS)
$(OBJS_BONUS):	$(HEADERS_BONUS)

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

.PHONY: all bonus clean fclean re norm
