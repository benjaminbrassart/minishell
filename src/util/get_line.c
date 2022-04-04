/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:05:00 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 04:14:20 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "minishell.h"
#include "type/t_sh.h"
#include "utils.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_line(t_sh *sh, char const *prompt)
{
	char	*line;
	int		res;

	if (sh->is_interactive)
		return (readline(prompt));
	res = get_next_line(STDIN_FILENO, &line);
	if (res < 0 || (res == 0 && (line == NULL || *line == 0)))
	{
		if (res == 0)
			free(line);
		else
			perror(PROGRAM_NAME);
		line = NULL;
	}
	return (line);
}
