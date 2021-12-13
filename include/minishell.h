/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 00:06:36 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/13 02:55:20 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COMMAND_PROMPT "$ "
# define PIPE_PROMPT "> "

# include <stddef.h>

void	handle_signal(int sig);

size_t	ft_strcspn(char const *s, char const *reject)
		__attribute__((nonnull(1, 2)));

char	*ft_strndup(char const *s, size_t n)
		__attribute__((nonnull(1), malloc));

void	*ft_memset(void *dst, int c, size_t n)
		__attribute__((nonnull(1)));

#endif
