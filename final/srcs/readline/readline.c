/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:37:08 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/18 14:37:21 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*print_line(t_rdline rd_line)
{
	char	*line;

	line = NULL;
	if (rd_line.line)
	{
		line = ft_strdup(rd_line.line);
		free(rd_line.line);
		rd_line.line = NULL;
	}
	return (line);
}

void	print_char_list(t_char_list *list)
{
	t_char_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->value != 0)
			ft_putchar_fd(tmp->value, 1);
		tmp = tmp->next;
	}
}

t_hist_list	*up_in_history(t_hist_list **history)
{
	if ((*history)->next)
	{
		*history = (*history)->next;
		if (*history)
		{
			(*history)->up_or_down = 1;
			print_char_list((*history)->char_list);
		}
	}
	else
	{
		if (history)
		{
			(*history)->up_or_down = 1;
			if ((*history)->char_list)
				print_char_list((*history)->char_list);
		}
	}
	return (*history);
}

t_hist_list	*down_in_history(t_hist_list **history)
{
	if ((*history))
	{
		if ((*history)->prev != NULL)
		{
			*history = (*history)->prev;
			(*history)->up_or_down = 1;
		}
		print_char_list((*history)->char_list);
	}
	return (*history);
}

int	rd_line(char **line, int *status, t_hist_list *history)
{
	t_rdline		rdline;
	struct termios	termios;
	struct termios	old_termios;

	ft_init_rdline(&rdline);
	set_terminal(&termios, &old_termios, rdline.term_fd);
	*line = ft_get_input(rdline, status, old_termios, history);
	reset_term(old_termios, rdline.term_fd);
	close(rdline.term_fd);
	return (1);
}
