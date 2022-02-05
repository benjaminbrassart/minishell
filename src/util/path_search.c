/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:40:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/05 12:13:57 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*path_join(char *dir_name, char *bin_name)
{
	char			*buffer;
	int				add_slash;
	size_t const	dir_len = ft_strlen(dir_name);
	size_t const	bin_len = ft_strlen(bin_name);

	add_slash = 1;
	if (dir_name[dir_len] == '/')
		add_slash = 0;
	buffer = malloc(sizeof (*buffer) * (dir_len + bin_len + add_slash + 1));
	if (buffer)
	{
		ft_memmove(buffer, dir_name, dir_len);
		ft_memmove(buffer + dir_len, "/", add_slash);
		ft_memmove(buffer + dir_len + add_slash, bin_name, bin_len);
		buffer[dir_len + add_slash + bin_len] = 0;
	}
	return (buffer);
}

static char	*path_search_entries(char **entries, char *bin_name)
{
	size_t	n;
	char	*path;

	n = 0;
	while (entries[n])
	{
		path = path_join(entries[n], bin_name);
		if (path && access(path, X_OK) == 0)
			return (path);
		free(path);
		++n;
	}
	return (NULL);
}

char	*path_search(t_env *env, char *bin_name)
{
	char *const	path_var = env_get(env, PATH_VAR_NAME);
	char		**path_entries;
	char		*exec;

	if (!path_var)
		return (NULL);
	path_entries = ft_split(path_var, ':');
	if (!path_entries)
		return (NULL);
	exec = path_search_entries(path_entries, bin_name);
	ft_split_destroy(path_entries);
	return (exec);
}
