/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:52:42 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/01 08:06:41 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include <stdlib.h>

static size_t	ft_split_size(char const *s, int c)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		while (*s && *s == c)
			++s;
		while (*s && *s != c)
			++s;
		if (*s == c)
			++size;
	}
	return (size);
}

void	*ft_split_destroy(char **array)
{
	char	*item;

	item = *array;
	while (item)
	{
		free(item);
		++item;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, int c)
{
	size_t const	size = ft_split_size(s, c);
	char			**array;
	size_t			i;
	size_t			j;

	array = malloc(sizeof (*array) * (size + 1));
	if (array)
	{
		ft_memset(array, 0, sizeof (*array) * (size + 1));
		i = 0;
		while (i < size)
		{
			while (*s == c)
				++s;
			j = 0;
			while (s[j] && s[j] != c)
				++j;
			array[i] = ft_strndup(s, j);
			if (!array[i])
				return (ft_split_destroy(array));
			s += j;
			++i;
		}
	}
	return (array);
}
