# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/27 04:08:31 by bbrassar          #+#    #+#              #
#    Updated: 2022/03/29 11:18:08 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					= libft.a

AR						= ar
ARFLAGS					= rs
RM						= rm -f

CC						= cc
CFLAGS					= -Wall -Wextra -Werror -c -MMD -MP -I.

DIR_SRC					= .
DIR_OBJ					= obj

SRC						= \
							ft_memset.c \
							ft_strcspn.c \
							ft_strndup.c \
							ft_strdup.c \
							ft_strjoin.c \
							ft_strlen.c \
							ft_strcmp.c \
							ft_split.c \
							ft_strncmp.c \
							ft_isspace.c \
							ft_memmove.c \
							ft_itoa.c \
							ft_isalnum.c \
							ft_isalpha.c \
							ft_strchr.c \
							ft_isdigit.c \
							ft_calloc.c \
							ft_strtrim.c \
							ft_strtoi.c \
							get_next_line.c
OBJ						= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
DEP						= $(OBJ:.o=.d)

$(NAME):				$(OBJ)
						$(AR) $(ARFLAGS) $@ $?

$(OBJ): $(DIR_OBJ)/%.o:	$(DIR_SRC)/%.c
						@mkdir -p $(@D)
						$(CC) $(CFLAGS) $< -o $@

-include $(DEP)

all:					$(NAME)

clean:
						$(RM) -r $(DIR_OBJ)

fclean:					clean
						$(RM) $(NAME)

re:						fclean all

.PHONY:					all clean fclean re
