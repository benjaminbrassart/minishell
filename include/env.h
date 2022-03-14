/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:13:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/14 15:39:38 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "type/t_env.h"
# include "type/t_sh.h"

# define PATH_VAR_NAME "PATH"

/**
 * Add an entry to an environment table
 */
void	__env_push(t_env_table *env, t_env *entry);

/**
 * Initialize an environment table with a main function's 3rd argument
 *
 * @return 0 if failed
 */
int		env_init(t_env_table *env, char *envp[]);

/**
 * Create a new entry
 *
 * @return NULL if malloc failed
 */
t_env	*env_new_entry(char const *key, char const *value);

/**
 * Destroy a whole environment table
 */
void	env_destroy(t_env_table *env);

/**
 * Get the value associated to a key in an environment table
 *
 * @return NULL if not found
 */
char	*env_get(t_env_table *env, char const *key);

/**
 * Get the value associated to a key in an environment table
 *
 * @param n the characters to compare
 * @return NULL if not found
 */
char	*env_getn(t_env_table *env, char const *key, size_t n);

/**
 * Set a value associated to a key in an environment table
 *
 * @return 0 if malloc failed
 */
int		env_set(t_env_table *env, char const *key, char const *value);

/**
 * Unset a value in an environment table
 */
void	env_unset(t_env_table *env, char const *key);

/**
 * Transform an enviornment table (linked list) to a envp (char *[])
 */
char	**env_toarray(t_env_table *env);

t_env	*env_from_literal(char const *env_entry);

#endif
