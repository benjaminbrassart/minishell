/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:52:42 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/12 10:07:01 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static size_t	ft_split_size(char const *s, int c)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		while (*s != c)
			++s;
		if (*s == c)
			++size;
	}
	return (size);
}

static void	*ft_split_destroy(char const ***array_p)
{
	char	*item;

	item = **array_p;
	while (item)
	{
		free(item);
		++item;
	}
	free(*array_p);
	return (NULL);
}

char	**ft_split(char const *s, int c)
{
	char	**array;
	size_t	size;
	size_t	j;

	size = ft_split_size(s, c);
	array = malloc(sizeof (*array) * (size + 1));
	if (array)
	{
		ft_memset(array, 0, sizeof (*array) * (size + 1));
		while (size)
		{
			--size;
			while (*s == c)
				++s;
			j = 0;
			while (s[j] && s[j] != c)
				++j;
			array[size] = ft_strndup(s, j);
			if (!array[size])
				return (ft_split_destroy(&array));
		}
	}
	return (array);
}
