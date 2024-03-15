/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:47:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/15 17:54:48 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

t_hist_list	*destroy_node(t_hist_list *node)
{
	if (node->char_list)
		delete_char_list(node->char_list);
	node->char_list = NULL;
	if (node->origin_char_list)
		delete_char_list(node->origin_char_list);
	node->origin_char_list = NULL;
	node->next = NULL;
	node->prev = NULL;
	free(node);
	node = NULL;
	return (NULL);
}

t_char_list	*free_list(t_char_list *list)
{
	t_char_list	*tmp;

	tmp = NULL;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

t_hist_list	*destroy_history(t_hist_list *history)
{
	t_hist_list	*last_node;
	t_hist_list	*tmp;

	tmp = NULL;
	last_node = history;
	if (last_node->next != NULL)
	{
		while (last_node->next != NULL)
			last_node = last_node->next;
	}
	tmp = last_node;
	while (tmp)
	{
		last_node = tmp;
		tmp = tmp->prev;
		last_node = destroy_node(last_node);
	}
	return (NULL);
}

int	check_history(t_hist_list **current, t_hist_list *history)
{
	if (*current && ((*current)->char_list == NULL
		|| (*current)->char_list->value == 0))
	{
		if (history)
			history = destroy_history(history);
		return (1);
	}
	return (0);
}
