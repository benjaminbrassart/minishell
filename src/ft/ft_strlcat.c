/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 09:07:08 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/22 12:11:28 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t dsize)
{
	const char	*odst = dst;
	const char	*osrc = src;
	size_t		n;
	size_t		dlen;

	n = dsize;
	while (n-- && *dst)
		dst++;
	dlen = dst - odst;
	n = dsize - dlen;
	if (!n--)
		return (dlen + strlen(src));
	while (*src)
	{
		if (n)
		{
			*dst++ = *src;
			n--;
		}
		++src;
	}
	*dst = 0;
	return (dlen + (src - osrc));
}
