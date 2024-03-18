/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:57:36 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/18 17:10:39 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	add_non_empty_list(long c, t_char_list **current)
{
	t_char_list	*tmp;

	tmp = NULL;
	tmp = *current;
	while (tmp->next)
	{
		ft_putchar_fd(tmp->value, 1);
		tmp = tmp->next;
	}
	ft_putchar_fd(tmp->value, 1);
	tmp->next = (t_char_list *)malloc(sizeof(t_char_list));
	if (!tmp->next)
		return ;
	tmp->next->next = NULL;
	tmp->next->value = c;
	tmp->next->len = tmp->len + 1;
	(*current)->len = tmp->next->len;
	ft_putchar_fd(c, 1);
}

void	add_char_list(char c, t_char_list **current)
{
	t_char_list	*tmp;

	tmp = NULL;
	if (*current == NULL || ((*current) && (*current)->value == 0))
	{
		ft_putchar_fd(c, 1);
		if (*current)
			free(*current);
		*current = (t_char_list *)malloc(sizeof(t_char_list));
		if (!(*current))
			return ;
		(*current)->value = c;
		(*current)->len = 1;
		(*current)->next = NULL;
	}
	else
		add_non_empty_list(c, current);
}

void	get_char(long c, t_hist_list *current)
{
	add_char_list(c, &current->char_list);
}
