/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 01:34:02 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/27 04:21:20 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include <stdlib.h>

char	*ft_strndup(char const *s, size_t n)
{
	char	*new_s;
	size_t	len;

	len = 0;
	while (len < n && s[len])
		++len;
	new_s = (char *)malloc(sizeof (*new_s) * (len + 1));
	if (new_s)
	{
		new_s[len] = 0;
		while (len--)
			new_s[len] = s[len];
	}
	return (new_s);
}
