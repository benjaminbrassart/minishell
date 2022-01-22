/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 07:47:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/11 07:54:35 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strncat(char *dst, char const *src, size_t n)
{
	char	*d;

	d = dst;
	if (n)
	{
		while (*dst)
			++dst;
		while (n-- && *src)
			*dst++ = *src++;
	}
	return (d);
}
