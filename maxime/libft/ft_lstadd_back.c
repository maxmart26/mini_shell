/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:49:50 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/05 22:10:47 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*data;

	data = *lst;
	if (!data)
		*lst = new;
	else
	{
		while (data.next != NULL)
		{
			data = data.next;
		}
		data.next = new;
	}
}
