# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 22:16:18 by bbrassar          #+#    #+#              #
#    Updated: 2022/04/04 10:42:40 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					= minishell

DIR_LIBFT				= libft
NAME_LIBFT				= $(DIR_LIBFT)/libft.a

CFLAGS					= -Wall -Werror -Wextra -c -MMD -MP -Iinclude -I$(DIR_LIBFT)
LDLIBS					= -lreadline -L$(DIR_LIBFT) -lft

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
							lexer/__lex_add.c \
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
							executor/exec_init.c \
							executor/exec_build.c \
							executor/exec_delete.c \
							executor/exec_build_redirect.c \
							executor/exec_redirect.c \
							executor/exec_delete_redirect.c \
							executor/run/exec_run.c \
							executor/run/exec_run_child.c \
							executor/run/exec_run_builtin.c \
							executor/run/exec_run_setup_child.c \
							executor/run/exec_run_destroy.c \
							executor/run/exec_run_cleanup.c \
							executor/run/exec_pipe.c \
							executor/run/exec_wait.c \
							executor/run/exec_pids_init.c \
							executor/run/exec_fork.c \
							util/path_search.c \
							util/command_count.c \
							util/open_red.c \
							util/ft_perror.c \
							util/str_expand.c \
							util/get_line.c \
							util/set_shlvl.c \
							lexer/heredoc/lex_heredoc.c \
							lexer/heredoc/lex_heredoc_delete.c \
							lexer/heredoc/lex_heredoc_read.c \
							lexer/heredoc/lex_heredoc_build.c \
							lexer/heredoc/lex_heredoc_write.c \
							lexer/heredoc/lex_heredoc_close.c \
							lexer/heredoc/lex_get_last_heredoc.c \
							lexer/heredoc/lex_close_last_heredoc.c
OBJ						= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
DEP						= $(OBJ:.o=.d)

$(NAME):				$(NAME_LIBFT) $(OBJ)
						$(CC) $(filter %.o,$^) -o $@ $(LDFLAGS) $(LDLIBS)

-include $(DEP)

$(OBJ): $(DIR_OBJ)/%.o:	$(DIR_SRC)/%.c
						@mkdir -p $(@D)
						$(CC) $(CFLAGS) $< -o $@

$(NAME_LIBFT):			.FORCE
						$(MAKE) -C $(DIR_LIBFT)

all:					$(NAME)

clean:
						$(RM) -r $(DIR_OBJ)

fclean:					clean
						$(RM) $(NAME)

re:						fclean all

-include mk/valgrind.mk

.FORCE:
.PHONY:					all clean fclean re
