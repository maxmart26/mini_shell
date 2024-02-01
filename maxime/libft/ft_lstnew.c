/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 07:56:57 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/05 22:10:47 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*data;

	data = malloc(1 * sizeof(t_list));
	if (!data)
		return (NULL);
	data.content = content;
	data.next = NULL;
	return (data);
}
