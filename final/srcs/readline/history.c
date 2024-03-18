/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:58:35 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/18 14:38:40 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

t_hist_list	*ft_init_history(long *c, int *newline_stop, t_hist_list *history)
{
	t_hist_list	*current;
	static int	is_init_history;

	is_init_history = 0;
	current = create_node();
	*c = 0;
	if (is_init_history == 0)
	{
		history = NULL;
		is_init_history = 1;
	}
	current->next = history;
	if (history)
		history->prev = current;
	history = current;
	*newline_stop = 1;
	return (current);
}

t_hist_list	*handle_history(long c, t_hist_list *current)
{
	if (current && c == D_KEY_UP)
		current = up_in_history(&current);
	else if (current && c == D_KEY_DOWN)
		current = down_in_history(&current);
	return (current);
}

int	add_node_history(t_rdline *rd_line, t_hist_list *current,
		t_hist_list **history)
{
	t_hist_list	*new_node;

	new_node = NULL;
	new_node = create_node();
	new_node->char_list = copy_char_list(current->char_list);
	new_node->origin_char_list = copy_char_list(current->char_list);
	delete_char_list(current->char_list);
	current->char_list = copy_char_list(current->origin_char_list);
	*history = delete_node_history(*history);
	if (new_node && new_node->char_list
		&& new_node->char_list->value != 0)
	{
		*history = insert_node_history(*history, new_node, 0);
		rd_line->line = create_line_from_list(new_node->char_list);
	}
	else
		destroy_node(new_node);
	ft_putstr_fd("\n", 1);
	return (0);
}

t_hist_list	*delete_node_history(t_hist_list *current)
{
	t_hist_list	*next_line;

	next_line = NULL;
	if (current == NULL)
		return (NULL);
	if (current->next)
		current->next->prev = current->prev;
	if (current->next)
		next_line = current->next;
	current = destroy_node(current);
	return (next_line);
}
