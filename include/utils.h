/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:38:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/15 13:40:12 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "type/t_env_table.h"
# include "type/t_token_list.h"
# include "type/t_exec.h"

size_t	command_count(t_token_list *list);

/**
 * Search an executable in the path variable
 *
 * @see PATH_VAR_NAME
 * @return NULL if malloc failed or not found
 */
char	*path_search(t_env_table *env, char const *bin_name);

int		open_red(t_exec_red *red);

/**
 * minishell: <name>: <msg>\n
 */
void	ft_perror(char const *name, char const *msg);

/**
 * minishell: <name>: <file>: <msg>\n
 */
void	ft_pferror(char const *name, char const *file, char const *msg);

/**
 * minishell: <name>: `<arg>': <msg>\n
 */
void	ft_paerror(char const *name, char const *arg, char const *msg);

#endif
