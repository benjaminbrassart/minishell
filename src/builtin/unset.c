/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:05:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/11 00:32:06 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"

int	builtin_unset(
	int argc,
	char *argv[],
	t_env_table *env
)
{
	int	n;

	n = 1;
	while (n < argc)
		env_unset(env, argv[n++]);
	return (0);
}
