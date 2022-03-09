/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 08:16:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/09 01:01:20 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include <stdlib.h>

static size_t	ft_itoa_size(int n)
{
	size_t			sz;

	sz = 1;
	while (n / 10)
	{
		++sz;
		n /= 10;
	}
	return (sz);
}

char	*ft_itoa(int n)
{
	size_t			sz;
	unsigned int	num;
	char			*s;

	sz = ft_itoa_size(n);
	s = ft_calloc(sz + !!(n < 0) + 1, sizeof (char));
	if (n < 0)
		num = -n;
	else
		num = n;
	if (s)
	{
		while (sz)
		{
			s[--sz + !!(n < 0)] = (num % 10) + '0';
			num /= 10;
		}
		if (n < 0)
			s[0] = '-';
	}
	return (s);
}
