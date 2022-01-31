/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:40:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 09:28:36 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "ft.h"
#include <dirent.h>
#include <stdio.h>

char	*path_search(t_sh *sh, char *bin_name)
{
	char *const		path = env_get(sh, PATH_VAR_NAME);
	char			**path_entries;
	size_t			n;
	DIR				*dir;
	struct dirent	*ent;

	if (!path)
		return (NULL);
	path_entries = ft_split(path, ':');
	if (!path_entries)
		return (NULL);
	n = 0;
	while (path_entries[n])
	{
		dir = opendir(path_entries[n]);
		if (dir)
		{
			while (1)
			{
				ent = readdir(dir);
				if (!ent)
					break ;
				if (ft_strcmp(bin_name, ent->d_name) == 0)
					return (ft_strjoin(path_entries[n], ent->d_name));
			}
			closedir(dir);
		}
		++n;
	}
	return (NULL);
}
