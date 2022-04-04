/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:04:23 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 02:43:23 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# define BUFFER_SIZE 4096

# include <stddef.h>

int		ft_strcmp(char const *s1, char const *s2);

size_t	ft_strcspn(char const *s, char const *reject);

char	*ft_strpbrk(char const *s, char const *accept);

char	*ft_strdup(char const *s)
		__attribute__((malloc));

char	*ft_strndup(char const *s, size_t n)
		__attribute__((malloc));

char	*ft_strncat(char *dst, char const *src, size_t n);

void	*ft_memset(void *dst, int c, size_t n);

void	*ft_memmove(void *dst, void const *src, size_t n);

size_t	ft_strlen(char const *s);

char	*ft_strjoin(char const *s1, char const *s2);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isspace(int c);

int		ft_isdigit(int c);

char	**ft_split(char const *s, char const *set);

void	*ft_split_destroy(char **array);

int		ft_strncmp(char const *s1, char const *s2, size_t n);

char	*ft_itoa(int i)
		__attribute__((malloc));

char	*ft_strchr(char const *s, int c);

void	*ft_calloc(size_t n, size_t size)
		__attribute__((malloc));

char	*ft_strtrim(char const *s)
		__attribute__((malloc));

int		ft_strtoi(char const *s, char **endptr);

int		get_next_line(int fd, char **line);

#endif
