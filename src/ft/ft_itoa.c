/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 08:16:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/01 08:50:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

unsigned int	ft_itoa_b(int i, t_itoa_buffer buffer)
{
	unsigned int	n;
	unsigned int	count;

	if (i < 0)
		n = -i;
	else
		n = i;
	count = 0;
	while (n || !count)
	{
		buffer[sizeof (t_itoa_buffer) - count++] = n % 10 + '0';
		n /= 10;
	}
	if (i < 0)
		buffer[sizeof (t_itoa_buffer) - count++] = '-';
	ft_memmove(buffer, buffer + sizeof (t_itoa_buffer) - count, count);
	ft_memset(buffer + count, 0, sizeof (t_itoa_buffer));
	return (count);
}

char	*ft_itoa(int i)
{
	t_itoa_buffer	digits;
	int const		count = ft_itoa_b(i, digits);

	return (ft_strndup(digits, count));
}
