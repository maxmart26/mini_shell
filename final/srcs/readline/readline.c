/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:37:08 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/12 18:26:10 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	rd_line(char **line, int *status)
{
	t_rdline		rdline;
	struct termios	termios;
	struct termios	old_termios;

	ft_init_rdline(&rdline);
	set_term(&termios, &old_termios, rdline.term_fd);
	*line = ft_get_input(rdline, status, old_termios);
	reset_term(old_termios, rdline.term_fd);
	close(rdline.term_fd);
}
