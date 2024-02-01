/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:47:58 by matorgue          #+#    #+#             */
/*   Updated: 2023/11/08 06:47:34 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc((ft_strlen(ptr) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (ptr[i])
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
