/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:45:11 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/13 15:07:05 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	ft_init_rdline(t_rdline *rdline)
{
	int	load_term;

	rdline->term_type = getenv("TERM");
	if (rdline->term_type == NULL)
		rdline->term_type = "xterm-256color";
	load_term = tgetent(NULL, rdline->term_type);
	if (!load_term)
	{
		ft_putstr_fd("Termcap database not accessible or \
		terminal type undefined in termcap", 1);
	}
	rdline->path = ttyname(1);
	rdline->term_fd = open(rdline->path, O_RDWR);
	if (!isatty(rdline->term_fd))
		ft_putstr_fd("fd does not point to terminal", 1);
	rdline->colums_count = tgetnum("co");
	rdline->line_count = tgetnum("li");
	rdline->cursor.col_position = 0;
	rdline->cursor.line_postion = 0;
	rdline->line = NULL;
}

void	set_terminal(struct termios *termios, struct termios *old, int fd)
{
	tcgetattr(fd, old);
	tcgetattr(fd, termios);
	termios->c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(fd, TCSANOW, termios);
}

void	reset_term(struct termios old_termios, int fd)
{
	tcsetattr(fd, TCSANOW, &old_termios);
}
