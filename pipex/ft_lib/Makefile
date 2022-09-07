# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 12:05:26 by dhyun             #+#    #+#              #
#    Updated: 2022/06/13 14:12:51 by dhyun            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror

AR	= ar
ARFLAGS	= rcs

RM	= rm -f

NAME	= libft.a

HEADERS	= ./include/libft.h ./include/get_next_line.h

DIR_LIBFT	= ./libft
DIR_GNL		= ./gnl
DIR_FT_PRINTF	= ./ft_printf

SRCS_LIBFT	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c\
			ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c\
			ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c\
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
			ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c\
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c\
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
			ft_putendl_fd.c ft_putnbr_fd.c ft_itoa_hexa.c\
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
			ft_lstmap.c
SRCS_GNL	= get_next_line.c get_next_line_utils.c
SRCS_FT_PRINTF	= ft_printf.c print_form.c

OBJS_LIBFT	= $(addprefix $(DIR_LIBFT)/, $(SRCS_LIBFT:.c=.o))
OBJS_GNL	= $(addprefix $(DIR_GNL)/, $(SRCS_GNL:.c=.o))
OBJS_FT_PRINTF	= $(addprefix $(DIR_FT_PRINTF)/, $(SRCS_FT_PRINTF:.c=.o))

OBJS		= $(OBJS_LIBFT) $(OBJS_GNL) $(OBJS_FT_PRINTF)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

$(OBJS):	$(HEADERS)

$(BONUS_OBJS):	$(HEADERS)

.PHONY:	all bonus clean fclean re
