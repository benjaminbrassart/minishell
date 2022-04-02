# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valgrind.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 16:12:07 by bbrassar          #+#    #+#              #
#    Updated: 2022/04/03 01:35:16 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VALGRIND			= valgrind
VALGRIND_OPT		+= --suppressions=readline.supp
VALGRIND_OPT		+= --trace-children=yes
VALGRIND_OPT		+= --track-origins=yes
VALGRIND_OPT		+= --track-fds=yes
VALGRIND_OPT		+= --leak-check=full
VALGRIND_OPT		+= --show-leak-kinds=all
EXC_NAME			= $(dir $(NAME))$(notdir $(NAME))

valgrind:
					@echo -e '\033[33m$(VALGRIND) \033[36m$(VALGRIND_OPT) \033[0m-- $(EXC_NAME)'
					@$(VALGRIND) $(VALGRIND_OPT) -- $(EXC_NAME)

.PHONY:				valgrind
