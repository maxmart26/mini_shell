/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:30:05 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/22 18:05:13 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_include.h"
#include "../include/minishell_proto.h"
#include "../include/minishell_struct.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
