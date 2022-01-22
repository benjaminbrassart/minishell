/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:13:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/12 11:45:09 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "type/env.h"
# include "type/sh.h"

int		env_init(t_sh *sh, char *ev[]);

t_env	*env_newent(char *key, char *value);

void	env_destroy(t_sh *sh);

char	*env_get(t_sh *sh, char const *key);

#endif
