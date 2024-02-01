/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:33:59 by matorgue          #+#    #+#             */
/*   Updated: 2023/11/07 08:34:01 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	f;

	f = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == f)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == f)
		return ((char *)s + i);
	return (NULL);
}
