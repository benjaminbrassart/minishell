# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 08:06:37 by bbrassar          #+#    #+#              #
#    Updated: 2022/04/01 08:07:26 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

CMDFILE="test_commands.txt"

RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
RESET=$(tput sgr0)

mkfifo .msh-pipe
mkfifo .bash-pipe

while read cmd; do
	printf -- "${BLUE}%s ${RESET}" "$cmd"
	msh_res="$(sed -e '1d;$d' -e 's/^minishell: //' < .msh-pipe)" &
	echo "$cmd" | ./minishell > .msh-pipe 2>&1
	msh_st="$?"
	bash_res="$(sed -e 's/^bash: line 1: //' < .bash-pipe)" &
	echo "$cmd" | bash > .bash-pipe 2>&1
	bash_st="$?"

	printf -- ""
	if [ "$msh_res" != "$bash_res" ]; then
		printf -- "${RED}KO! (output)\n"
		printf -- "  ${GREEN}-> %-9s: '${YELLOW}$bash_res${GREEN}'${RESET}\n" "bash"
		printf -- "  ${RED}-> %-s: '${YELLOW}$msh_res${RED}'${RESET}" "minishell"
	fi
	if [ "$msh_st" != "$bash_st" ]; then
		printf -- "${RED}KO! (status)\n"
		printf -- "  ${GREEN}-> %-9s: '${YELLOW}$bash_st${GREEN}'${RESET}\n" "bash"
		printf -- "  ${RED}-> %-s: '${YELLOW}$msh_st${RED}'${RESET}" "minishell"
	fi
	printf "\n"
done < "$CMDFILE"

rm -f .msh-pipe
rm -f .bash-pipe
