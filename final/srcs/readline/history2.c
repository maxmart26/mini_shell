/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:47:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/18 14:35:51 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

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

t_hist_list	*insert_node_history(t_hist_list *history, t_hist_list *new_node,
		int is_hist)
{
	if (!history)
	{
		new_node->history = is_hist;
		new_node->index = 1;
		history = new_node;
		history->next = NULL;
		history->prev = NULL;
	}
	else
		history = push_node_history(&history, new_node, is_hist);
	return (history);
}

char	*create_line_from_list(t_char_list *list)
{
	t_char_list	*tmp;
	char		*line;
	int			len;
	int			i;

	i = 0;
	len = list->len;
	tmp = list;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (ft_putstr_fd("Allocation problem", 1), NULL);
	ft_bzero(line, len + 1);
	while (tmp)
	{
		line[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	line[len] = '\0';
	return (line);
}
