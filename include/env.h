/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:13:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 02:45:12 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "type/t_env.h"
# include "type/t_sh.h"

# define PATH_VAR_NAME "PATH"

void	__env_push(t_env_table *env, t_env *entry);

int		env_init(t_env_table *env, char *envp[]);

t_env	*env_new_entry(char const *key, char const *value);

void	env_destroy(t_env_table *env);

char	*env_get(t_env_table *env, char const *key);

char	*env_getn(t_env_table *env, char const *key, size_t n);

int		env_set(t_env_table *env, char const *key, char const *value);

char	*path_search(t_env_table *env, char const *bin_name);

#endif
