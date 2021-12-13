# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 22:16:18 by bbrassar          #+#    #+#              #
#    Updated: 2021/12/13 01:42:17 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell
DIR_LIBFT			= libft
NAME_LIBFT			= $(DIR_LIBFT)/libft.a

CFLAGS				= -Wall -Werror -Wextra -c -MMD -MP -Iinclude
# LDFLAGS				= -L$(DIR_LIBFT)
# LDLIBS				= -lreadline -lft
LDLIBS					= -lreadline

ifeq ($(DEBUG), true)
CFLAGS				+= -g3
endif

DIR_SRC				= src
DIR_OBJ				= obj
SRC					= \
						main.c \
						ft/ft_memset.c \
						ft/ft_strcspn.c \
						ft/ft_strndup.c \
						lexer/lex_dump.c \
						lexer/lex_tokenize.c \
						lexer/lex_delete.c
OBJ					= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
DEP					= $(OBJ:.o=.d)

$(NAME):			$(OBJ)
					$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

-include $(DEP)

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) $< -o $@

all:				$(NAME)

clean:
					$(RM) -r $(DIR_OBJ)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
