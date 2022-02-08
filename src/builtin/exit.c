/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:06:36 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 02:51:03 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(
	int argc __attribute__((unused)),
	char *argv[] __attribute__((unused)),
	t_env_table *env __attribute__((unused))
)
{
	(void)env;
	return (0);
}
