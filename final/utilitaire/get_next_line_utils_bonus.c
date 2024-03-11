/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:53:43 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/11 12:39:08 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:39:12 by matorgue          #+#    #+#             */
/*   Updated: 2023/11/18 09:49:06 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../include/minishell_include.h"
#include "../include/minishell_proto.h"
#include "../include/minishell_struct.h"

char	*ft_cut(char *stockage)
{
	char	*str;
	int		i;

	if (stockage[0] == '\0')
		return (free(stockage), NULL);
	i = 0;
	while (stockage[i] && stockage[i] != '\n')
		i++;
	if (stockage[i] == '\n')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (stockage[i] && stockage[i] != '\n')
	{
		str[i] = stockage[i];
		i++;
	}
	if (stockage[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	if (str[0] == 0)
		return (NULL);
	return (str);
}

char	*ft_strjoin_suite(char *stockage, char *buffer, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (stockage[i])
	{
		str[i] = stockage[i];
		i++;
	}
	while (buffer[j])
	{
		str[i + j] = buffer[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
