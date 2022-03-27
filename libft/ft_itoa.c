/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 08:16:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/09 10:45:24 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include <stdlib.h>

char	*ft_itoa(int i)
{
	char			buffer[11];
	unsigned int	n;
	unsigned int	pos;

	if (i < 0)
		n = -i;
	else
		n = i;
	pos = 0;
	while (n > 0 || pos == 0)
	{
		buffer[sizeof (buffer) - ++pos] = n % 10 + '0';
		n /= 10;
	}
	if (i < 0)
		buffer[sizeof (buffer) - ++pos] = '-';
	return (ft_strndup(buffer + sizeof (buffer) - pos, pos));
}
