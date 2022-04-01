#!/bin/bash

CMDFILE="test_commands.txt"

RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
RESET=$(tput sgr0)

while read cmd; do
	printf -- "${BLUE}%s ${RESET}" "$cmd"
	msh_res=$(echo "$cmd" | (./minishell 2>&1; msh_st="$?") | sed -e '1d;$d' -e 's/^minishell: //')
	bash_res=$(echo "$cmd" | (bash 2>&1; bash_st="$?") | sed -e 's/^bash: line 1: //')

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
