/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:23:44 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/18 12:51:45 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

t_hist_list	*create_node(void)
{
	t_hist_list	*node;

	node = (t_hist_list *)malloc(sizeof(t_hist_list));
	if (!node)
		return (NULL);
	node->char_list = NULL;
	node->origin_char_list = NULL;
	node->up_or_down = 0;
	node->next = NULL;
	node->prev = NULL;
	node->value = 0;
	node->history = 0;
	return (node);
}

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

t_hist_list	*push_node_history(t_hist_list **history, t_hist_list *new_node,
		int is_hist)
{
	t_hist_list	*tmp;

	tmp = *history;
	if (new_node)
	{
		if ((*history)->prev != NULL)
		{
			while ((*history)->prev != NULL)
				*history = (*history)->prev;
		}
		new_node->history = is_hist;
		new_node->next = (*history);
		new_node->index = (*history)->index + 1;
		new_node->prev = NULL;
		(*history)->prev = new_node;
		(*history) = new_node;
	}
	return (*history);
}
