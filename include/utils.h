/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:38:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/03 05:18:18 by bbrassar         ###   ########.fr       */
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

/**
 * expand a string, getting environment variables from env
 */
char	*str_expand(t_env_table *env, char const *s);

/**
 * get a line, with a prompt if sh is in interactive mode
 */
char	*get_line(t_sh *sh, char const *prompt);

/**
 * set environment variable SHLVL
 */
int		set_shlvl(t_env_table *env);

#endif
