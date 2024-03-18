/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:30:58 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/18 17:09:21 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	handle_ctrl_c(t_hist_list **current, int *status, t_hist_list *history)
{
	if (*current && (*current)->char_list == NULL
		&& (*current)->origin_char_list == NULL && (*current)->prev == NULL)
		history = delete_node_history((*current));
	else
	{
		delete_char_list((*current)->char_list);
		(*current)->char_list = copy_char_list((*current)->origin_char_list);
		history = delete_node_history((*current));
	}
	*status = 1;
	ft_putstr_fd("\n", 1);
	return (0);
}

void	handle_ctrl_d(int *status, t_rdline rd_line,
		struct termios old_term)
{
	reset_term(old_term, rd_line.term_fd);
	*status = 127;
	ft_putstr_fd("exit", 1);
	exit(*status);
}

char	*ft_get_input(t_rdline rdline, int *status, struct termios old_term,
		t_hist_list *history)
{
	long		c;
	t_hist_list	*current;
	int			newline_stop;

	current = ft_init_history(&c, &newline_stop, history);
	while (newline_stop == 1)
	{
		read(rdline.term_fd, &c, 6);
		if (current && (c == D_KEY_UP || c == D_KEY_DOWN))
			current = handle_history(c, current);
		else if (c == D_KEY_ENTER)
			newline_stop = add_node_history(&rdline, current, &history);
		else if (c == D_KEY_CTRL_C)
			newline_stop = handle_ctrl_c(&current, status, history);
		else if (c == D_KEY_CTRL_D)
		{
			if (check_history(&current, history) == 1)
				handle_ctrl_d(status, rdline, old_term);
		}
		else if (ft_isprint(c))
			get_char(c, current);
		c = 0;
	}
	return (print_line(rdline));
}
