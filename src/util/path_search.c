/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:40:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 02:21:49 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "env.h"
#include "ft.h"
#include "utils.h"
#include "minishell.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

static char	*path_join(char const *dir_name, char const *bin_name)
{
	t_buffer	buffer;

	buffer_init(&buffer);
	if (buffer_append(&buffer, dir_name)
		&& buffer_cappend(&buffer, '/')
		&& buffer_append(&buffer, bin_name)
		&& buffer_flush(&buffer))
		return (buffer.buf);
	buffer_delete(&buffer);
	return (NULL);
}

static char	*path_search_entries(char **entries, char const *bin_name)
{
	struct stat	st;
	size_t		n;
	char		*path;

	n = 0;
	while (entries[n])
	{
		path = path_join(entries[n], bin_name);
		if (path && stat(path, &st) == 0
			&& !S_ISDIR(st.st_mode) && access(path, X_OK) == 0)
			return (path);
		free(path);
		++n;
	}
	return (NULL);
}

char	*path_search(t_env_table *env, char const *bin_name)
{
	char *const	path_var = env_get(env, PATH_VAR_NAME);
	char		**path_entries;
	char		*exec;

	if (!path_var)
		return (NULL);
	path_entries = ft_split(path_var, PATH_SEPARATOR);
	if (path_entries == NULL)
	{
		perror(PROGRAM_NAME);
		return (NULL);
	}
	exec = path_search_entries(path_entries, bin_name);
	ft_split_destroy(path_entries);
	return (exec);
}
