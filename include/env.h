/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:13:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 00:51:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "type/t_env.h"
# include "type/t_sh.h"

# define PATH_VAR_NAME "PATH"

int		env_init(t_env **env_p, char *ev[]);

t_env	*env_newent(char *key, char *value);

void	env_destroy(t_env **env_p);

char	*env_get(t_env *env, char const *key);

char	*env_getn(t_env *env, char const *key, size_t n);

char	*path_search(t_env *env, char *bin_name);

#endif
