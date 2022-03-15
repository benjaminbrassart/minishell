# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 22:16:18 by bbrassar          #+#    #+#              #
#    Updated: 2022/03/15 13:34:47 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					= minishell
DIR_LIBFT				= libft
NAME_LIBFT				= $(DIR_LIBFT)/libft.a

CFLAGS					= -Wall -Werror -Wextra -c -MMD -MP -Iinclude
LDLIBS					= -lreadline

DEBUG					= true

ifeq ($(DEBUG), true)
CFLAGS					+= -g3
endif

DIR_SRC					= src
DIR_OBJ					= obj
SRC						= \
							main.c \
							setup.c \
							signal/sigint.c \
							signal/sigquit.c \
							signal/get_exit_status.c \
							builtin/get_builtin.c \
							builtin/cd.c \
							builtin/echo.c \
							builtin/pwd.c \
							builtin/export.c \
							builtin/unset.c \
							builtin/env.c \
							builtin/exit.c \
							buffer/buffer_init.c \
							buffer/buffer_delete.c \
							buffer/buffer_flush.c \
							buffer/buffer_append.c \
							ft/ft_memset.c \
							ft/ft_strcspn.c \
							ft/ft_strndup.c \
							ft/ft_strdup.c \
							ft/ft_strjoin.c \
							ft/ft_strlen.c \
							ft/ft_strcmp.c \
							ft/ft_split.c \
							ft/ft_strncmp.c \
							ft/ft_isspace.c \
							ft/ft_memmove.c \
							ft/ft_itoa.c \
							ft/ft_isalnum.c \
							ft/ft_isalpha.c \
							ft/ft_strchr.c \
							ft/ft_isdigit.c \
							ft/ft_calloc.c \
							lexer/__lex_add.c \
							lexer/lex_dump.c \
							lexer/lex_tokenize.c \
							lexer/lex_delete.c \
							lexer/lex_add_token.c \
							lexer/lex_expand.c \
							lexer/lex_postexpand.c \
							lexer/lex_concat.c \
							lexer/lex_check_syntax.c \
							lexer/tokenizer/get_tokenizer.c \
							lexer/tokenizer/tokenize_dgreat.c \
							lexer/tokenizer/tokenize_dless.c \
							lexer/tokenizer/tokenize_great.c \
							lexer/tokenizer/tokenize_less.c \
							lexer/tokenizer/tokenize_pipe.c \
							lexer/tokenizer/tokenize_word_dquote.c \
							lexer/tokenizer/tokenize_word_nquote.c \
							lexer/tokenizer/tokenize_word_squote.c \
							env/__env_push.c \
							env/env_destroy.c \
							env/env_get.c \
							env/env_init.c \
							env/env_new_entry.c \
							env/env_set.c \
							env/env_unset.c \
							env/env_toarray.c \
							env/env_from_literal.c \
							executor/exec_build.c \
							executor/exec_run.c \
							executor/exec_delete.c \
							executor/exec_pipe.c \
							executor/exec_build_redirect.c \
							executor/exec_redirect.c \
							executor/exec_empty.c \
							util/path_search.c \
							util/command_count.c \
							util/open_red.c \
							util/ft_perror.c \
							lexer/heredoc/lex_heredoc.c \
							lexer/heredoc/lex_heredoc_delete.c \
							lexer/heredoc/lex_heredoc_read.c \
							lexer/heredoc/lex_heredoc_build.c \
							lexer/heredoc/lex_heredoc_write.c

OBJ						= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
DEP						= $(OBJ:.o=.d)

$(NAME):				$(OBJ)
						$(CC) -g3 $^ -o $@ $(LDFLAGS) $(LDLIBS)

-include $(DEP)

$(OBJ): $(DIR_OBJ)/%.o:	$(DIR_SRC)/%.c
						@mkdir -p $(@D)
						$(CC) $(CFLAGS) $< -o $@

all:					$(NAME)

clean:
						$(RM) -r $(DIR_OBJ)

fclean:					clean
						$(RM) $(NAME)

re:						fclean all

-include mk/valgrind.mk

.PHONY:					all clean fclean re
