/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:24:45 by matorgue          #+#    #+#             */
/*   Updated: 2023/11/09 07:27:02 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(dst);
	if (size <= len)
		return (size + ft_strlen((char *)src));
	while (dst[i] && i < size)
		i++;
	while (src[j] && i < size - 1)
	{
		dst[i++] = src[j++];
	}
	if (size != 0 && size >= len)
		dst[i] = '\0';
	return (len + ft_strlen((char *)src));
}
/*#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <bsd/string.h>

int	main(void)
{
	char	dest[30];

	printf("%zu", ft_strlcat(dest, "123", 0));
	printf("%d",strcmp(dest, ""));
	printf("%s",dest);
}*/
