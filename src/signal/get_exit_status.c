/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:45:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/02 15:49:57 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"
#include <wait.h>

int	get_exit_status(int raw_status)
{
	if (WIFEXITED(raw_status))
		return (WEXITSTATUS(raw_status));
	if (WIFSIGNALED(raw_status))
		return (WTERMSIG(raw_status) + EXIT_STATUS_SIGNAL_OFFSET);
	if (WIFSTOPPED(raw_status))
		return (WSTOPSIG(raw_status) + EXIT_STATUS_SIGNAL_OFFSET);
	return (raw_status);
}
