/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:40:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/12 11:45:30 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

char	*path_search(t_sh *sh, char *bin_rel)
{
	t_env	*env;
	char	*raw_path;

	raw_path = env_get(sh, "PATH");
	if (!raw_path)
	env = sh->env;
}
