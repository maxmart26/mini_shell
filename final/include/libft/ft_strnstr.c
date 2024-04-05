/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:49:25 by lnunez-t          #+#    #+#             */
/*   Updated: 2023/11/13 11:52:27 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_nd;

	i = 0;
	if (!little || !big)
		return (NULL);
	if (ft_strlen(little) == 0)
		return ((char *)big);
	len_nd = ft_strlen(little);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && big[i + j] == little[j] && i + j < len)
			j++;
		if (j == len_nd)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
