# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valgrind.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 16:12:07 by bbrassar          #+#    #+#              #
#    Updated: 2022/03/02 17:19:53 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

valgrind:
					@valgrind \
					--suppressions=readline.supp \
					--leak-check=full \
					--show-leak-kinds=all \
					--track-fds=yes \
					./$(NAME)

.PHONY:				valgrind
