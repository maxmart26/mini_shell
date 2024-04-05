/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:18:53 by lnunez-t          #+#    #+#             */
/*   Updated: 2023/11/13 11:48:15 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	pos;
	size_t	i;

	dst_len = ft_strlen(dst);
	pos = 0;
	i = 0;
	if (size <= dst_len)
		return (ft_strlen((char *)src) + size);
	while (dst[pos] && pos < size)
		pos++;
	while (src[i] && pos < size - 1)
		dst[pos++] = src[i++];
	if (size != 0 && size >= dst_len)
		dst[pos] = '\0';
	return (ft_strlen((char *)src) + dst_len);
}
