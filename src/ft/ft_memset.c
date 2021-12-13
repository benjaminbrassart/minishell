/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 01:38:04 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/13 01:39:09 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *dst, int c, size_t n)
{
	unsigned char		*d;
	unsigned char const	ch = c;

	d = (unsigned char *)dst;
	while (n--)
		*d++ = ch;
	return (dst);
}
