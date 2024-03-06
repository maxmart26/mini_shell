/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:25:05 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/22 18:03:08 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_include.h"
#include "../include/minishell_proto.h"
#include "../include/minishell_struct.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*tab;

	i = 0;
	tab = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
