/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:57:55 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/01/30 18:31:57 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (nmemb * size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb > -1 / size)
		return (NULL);
	tab = malloc((nmemb * size));
	if (!tab)
		return (free(tab), NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
