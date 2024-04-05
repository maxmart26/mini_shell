/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:final/include/libft/ft_strcmp.c
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
========
/*   exit.c                                             :+:      :+:    :+:   */
>>>>>>>> laura:final/srcs/exec/builting/exit.c
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:final/include/libft/ft_strcmp.c
/*   Created: 2024/03/27 07:16:34 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/27 07:17:26 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - s2[i]);
========
/*   Created: 2024/03/12 16:21:03 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/25 15:24:02 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	ft_exit(int i)
{
	if (i == 0)
		exit(158);
	else
	{
		exit(1);
	}
>>>>>>>> laura:final/srcs/exec/builting/exit.c
}
