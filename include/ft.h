/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:04:23 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/19 17:04:49 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <stddef.h>

int		ft_strcmp(char const *s1, char const *s2);

size_t	ft_strcspn(char const *s, char const *reject);

char	*ft_strdup(char const *s)
		__attribute__((malloc));

char	*ft_strndup(char const *s, size_t n)
		__attribute__((malloc));

char	*ft_strncat(char *dst, char const *src, size_t n);

void	*ft_memset(void *dst, int c, size_t n);

size_t	ft_strlen(char const *s);

char	*ft_strjoin(char const *s1, char const *s2);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

#endif
