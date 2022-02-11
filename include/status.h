/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:35:22 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/11 01:12:44 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

# include <signal.h>

# define EXIT_STATUS_OK 0
# define EXIT_STATUS_MINOR 1
# define EXIT_STATUS_MAJOR 2
# define EXIT_STATUS_MAX 256

/* Content of $? */
static volatile int	g_exit_status;

#endif
