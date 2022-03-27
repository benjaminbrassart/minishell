/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 07:40:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/27 04:21:48 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

size_t	ft_nsstrlen(char const *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		++len;
	return (len);
}
