/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 07:30:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 07:31:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include <stdlib.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*bytes;

	bytes = malloc(n * size);
	if (bytes)
		ft_memset(bytes, 0, n * size);
	return (bytes);
}
