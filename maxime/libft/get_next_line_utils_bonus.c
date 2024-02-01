/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:39:12 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/10 15:45:31 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"

char	*ft_strnchr(char *const str, char const c, size_t const n)
{
	size_t	i;

	i = 0;
	while (str[i] && i < n)
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

void	*ft_memcpy(
	void *const dest,
	void const *const src,
	size_t size)
{
	char	*ptr1;
	char	*ptr2;

	ptr1 = (char *)dest;
	ptr2 = (char *)src;
	while (size--)
	{
		*ptr1 = *ptr2;
		ptr1++;
		ptr2++;
	}
	return (dest);
}
