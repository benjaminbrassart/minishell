/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:07:31 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/20 13:58:56 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_strtrim(char const *s)
{
	size_t	n;

	while (ft_isspace(*s))
		++s;
	if (*s == 0)
		return (ft_calloc(1, sizeof (*s)));
	n = ft_strlen(s);
	while (n && ft_isspace(s[n - 1]))
		--n;
	return (ft_strndup(s, n));
}
