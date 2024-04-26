/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sep2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:34:54 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/26 13:54:36 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*manage_sep2(char *str, char *result, int i, int j)
{
	int (is_space) = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			result[j++] = str[i++];
			is_space = 0;
		}
		else if (!is_space && str[i + 1] != '\0')
		{
			result[j++] = ' ';
			is_space = word_with_quote(str);
			i++;
		}
		else if (!is_space && str[i + 1] == '\0')
		{
			result[j++] = ' ';
			break ;
		}
		else
			i++;
	}
	result[j] = '\0';
	return (result);
}

int	word_with_quote(char *str)
{
	int	is_space;

	if (str[0] == '\'' || str[0] == '\"')
		is_space = 0;
	else
		is_space = 1;
	return (is_space);
}
