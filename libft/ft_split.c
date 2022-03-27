/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:40:29 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/03 21:40:32 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include <stdlib.h>

static size_t	ft_split_size(char const *s, int c)
{
	size_t	size;
	int		j;

	size = 0;
	while (*s)
	{
		while (*s && *s == c)
			++s;
		j = 0;
		while (s[j] && s[j] != c)
			++j;
		if (j > 0)
			++size;
		s += j;
	}
	return (size);
}

void	*ft_split_destroy(char **array)
{
	int	n;

	n = 0;
	if (array)
	{
		while (array[n])
			free(array[n++]);
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
		array[size] = NULL;
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
