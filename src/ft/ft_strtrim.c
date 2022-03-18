/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:07:31 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/18 19:13:41 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_strtrim(char const *s)
{
	int	last;
	int	n;

	while (ft_isspace(*s))
		++s;
	n = 0;
	last = 0;
	while (s[n])
	{
		if (!ft_isspace(s[n]))
			last = n;
		++n;
	}
	return (ft_strndup(s, last));
}
