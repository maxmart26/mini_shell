/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:55:48 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/21 14:43:55 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"


void	def_index(t_token *list)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp->next)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

t_token	*index_first(t_token *list)
{
	t_token	*result;

	while (list->type == SEP)
		list = list->next;
	result = list;
	return (result);
}

t_token	*remove_sep(t_token *list)
{
	t_token	*tmp;
	t_token	*result;

	result = list;
	while (list)
	{
		if (list->type == SEP)
		{
			if (list->index == 0)
				result = index_first(list);
			else
			{
				tmp = list->prev;
				tmp->next = list->next;
				tmp->next->prev = tmp;
				free(list);
				list = tmp;
			}
		}
		tmp = list->next;
		list = tmp;
	}
	return (result);
}
