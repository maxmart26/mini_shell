/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:36:57 by matorgue          #+#    #+#             */
/*   Updated: 2024/02/21 18:29:30 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_include.h"
#include "../include/minishell_proto.h"
#include "../include/minishell_struct.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = n;
	if (nb == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < nb - 1)
		i++;
	return ((unsigned char)s1[i] - s2[i]);
}
