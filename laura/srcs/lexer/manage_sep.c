/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:55:48 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/22 15:50:03 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
			{
				list = list->next;
				result = list;
			}
			else
			{
				tmp = list->prev;
				tmp->next = list->next;
				free(list);
				list = tmp;
			}
		}
		tmp = list->next;
		list = tmp;
	}
	return (result);
}
