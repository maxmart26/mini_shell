/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:34:45 by matorgue          #+#    #+#             */
/*   Updated: 2023/11/08 07:02:36 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	f;
	int		i;
	int		new;

	f = (unsigned char)c;
	i = 0;
	new = -1;
	while (s[i])
	{
		if (s[i] == f)
			new = i;
		i++;
	}
	if (s[i] == f)
			new = i;
	if (new != -1)
		return ((char *)s + new);
	return (NULL);
}
