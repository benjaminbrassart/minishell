/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 04:48:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 06:11:36 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define REDIRECTION_UMASK 0644
# define MESSAGE_CHILD_QUIT "Quit"
# define MESSAGE_CHILD_SEGV "Segmentation fault"
# define MESSAGE_COMMAND_NF "Command not found"
# define MESSAGE_EXEC_DIR "Is a directory"

# include "type/t_exec.h"
# include <sys/types.h>

int		exec_init(t_token_list *list, t_exec_meta *meta);

int		exec_build(t_token_list *list, t_exec_meta *meta_p);

int		exec_build_redirect(t_exec_meta *meta);

int		exec_redirect(t_exec *exec);

int		exec_run(t_exec_meta *meta);

void	exec_delete(t_exec_meta *meta);

void	exec_delete_redirect(t_exec_meta *meta);

void	close_fds(t_exec_meta *meta);

void	parent_close(t_exec_meta *meta, int index);

void	child_destroy(t_exec *exec);

void	exec_run_setup_child(t_exec *exec);

void	exec_run_child(t_exec *exec)
		__attribute__((noreturn));

void	exec_run_builtin(t_exec *exec);

void	exec_run_cleanup(t_exec_meta *meta, pid_t *pids);

pid_t	*exec_pids_init(t_exec_meta *meta);

int		exec_pipe(t_exec *exec);

void	exec_wait(t_exec_meta *meta, pid_t *pids);

void	exec_fork(t_exec *exec)
		__attribute__((noreturn));

#endif
