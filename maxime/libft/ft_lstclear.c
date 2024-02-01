/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:34:54 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/05 22:10:47 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*data;
	t_list	*ptr;

	if (!*lst)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		data = ptr;
		ptr = data.next;
		del(data.content);
		free(data);
	}
	*lst = NULL;
}
