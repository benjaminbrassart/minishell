/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 02:31:39 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 11:47:31 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_strpbrk(char const *s, char const *accept)
{
	char const	*p;

	p = s;
	while (*p != 0 && ft_strchr(accept, *p) == NULL)
		++p;
	if (*p == 0)
		p = NULL;
	return ((char *)p);
}
