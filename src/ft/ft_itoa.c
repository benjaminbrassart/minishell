/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 08:16:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/12 08:04:36 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itoa(int i)
{
	char			digits[MAX_INT_DIGITS];
	unsigned int	n;
	unsigned int	count;

	if (i < 0)
		n = -i;
	else
		n = i;
	count = 0;
	while (n || !count)
	{
		digits[sizeof (digits) - count++] = n % 10 + '0';
		n /= 10;
	}
	if (i < 0)
		digits[sizeof (digits) - count++] = '-';
	return (ft_strndup(digits + sizeof (digits) - count, count));
}
