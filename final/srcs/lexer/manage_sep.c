/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:55:48 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/25 13:29:18 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	def_index(t_token *list)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp->next)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

t_token	*index_first(t_token *list)
{
	t_token	*result;

	while (list->type == SEP)
		list = list->next;
	result = list;
	return (result);
}

t_token	*remove_sep(t_token *list)
{
	t_token	*tmp;
	t_token	*result;

	result = list;
	while (list)
	{
		if (list->type == SEP)
		{
			if (list->index == 0)
				result = index_first(list);
			else
			{
				tmp = list->prev;
				tmp->next = list->next;
				tmp->next->prev = tmp;
				free(list->value);
				free(list);
				list = tmp;
			}
		}
		tmp = list->next;
		list = tmp;
	}
	return (result);
}

char	*delete_sep(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		is_space;

	i = 0;
	result = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	is_space = 0;
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
			is_space = 1;
			i++;
		}
		else if (!is_space && str[i + 1] == '\0')
		{
			result[j] = ' ';
			j++;
			break ;
		}
		else
			i++;
	}
	free(str);
	result[j] = '\0';
	return (result);
}
