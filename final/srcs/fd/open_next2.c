/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_next2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:52:51 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/01 11:31:59 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	init_fd(t_token *token)
{
	while (token)
	{
		token->fd_int = 0;
		token->fd_out = 1;
		token = token->next;
	}
}

int	verif_open(t_token *token)
{
	if (g_status == 258)
		return (0);
	while (token)
	{
		if (token->type == APPEND || token->type == GREAT || token->type == LESS
			|| token->type == HEREDOC)
			return (1);
		token = token->next;
	}
	return (0);
}
void	close_end(int  fd, int  fd2)
{
	if (fd > 2)
		close(fd);
	if (fd2 > 2)
		close(fd2);
}
