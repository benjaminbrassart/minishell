/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:03:47 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/02 16:41:32 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLER_H
# define SIGHANDLER_H

void	sigquit_default(void);
void	sigquit_ignore(void);
void	sigquit_install(void);

void	sigint_default(void);
void	sigint_ignore(void);
void	sigint_install(void);
void	handle_sigint(int sig);

#endif
