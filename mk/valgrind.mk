# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valgrind.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 16:12:07 by bbrassar          #+#    #+#              #
#    Updated: 2022/04/01 03:00:24 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VALGRIND			= valgrind
VALGRIND_OPT		= \
					--suppressions=readline.supp \
					--leak-check=full \
					--show-leak-kinds=all \
					--trace-children=yes \
					--track-fds=yes
EXC_NAME			= $(dir $(NAME))$(notdir $(NAME))

valgrind:
					@echo -e '\033[33m$(VALGRIND) \033[36m$(VALGRIND_OPT) \033[0m-- $(EXC_NAME)'
					@$(VALGRIND) $(VALGRIND_OPT) -- $(EXC_NAME)

.PHONY:				valgrind
