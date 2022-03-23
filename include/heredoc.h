/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 06:05:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/23 03:31:34 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# define HEREDOC_PROMPT "heredoc> "

# include "type/t_exec.h"
# include "type/t_heredoc.h"
# include "type/t_token_list.h"

int		lex_heredoc(t_token_list *list, t_heredoc *heredoc);

int		lex_heredoc_build(t_token_list *list, t_heredoc *heredoc);

void	lex_heredoc_delete(t_heredoc *heredoc);

int		lex_heredoc_read(t_heredoc *heredoc);

int		lex_heredoc_write(t_exec *exec);

#endif
