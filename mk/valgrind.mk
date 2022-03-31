# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valgrind.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 16:12:07 by bbrassar          #+#    #+#              #
#    Updated: 2022/03/31 21:00:30 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

valgrind:
					@valgrind \
					--suppressions=readline.supp \
					--leak-check=full \
					--show-leak-kinds=all \
					--trace-children=yes \
					--track-fds=yes \
					./$(NAME)

.PHONY:				valgrind
