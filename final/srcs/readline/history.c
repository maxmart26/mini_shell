/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:58:35 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/13 16:50:48 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

t_list	*create_node(void)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
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

t_list	*ft_init_history(long *c, int *newline_stop)
{
	t_list 		*current;
	static int	is_init_history;

	is_init_history = 0;
	current = create_node();
	*c = 0;
	if (is_init_history == 0)
