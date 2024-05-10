/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:55:48 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/10 13:22:18 by matorgue         ###   ########.fr       */
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
	t_token	*tmp;

	while (list->type == SEP)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
		list->prev = NULL;
	}
	result = list;
	result->prev = NULL;
	return (result);
}

t_token	*removee(t_token *list)
{
	t_token *(tmp) = NULL;
	tmp = list->prev;
	tmp->next = list->next;
	tmp->next->prev = tmp;
	free(list->value);
	free(list);
	list = tmp;
	return (list);
}

t_token	*remove_sep(t_token *list)
{
	while (list)
	{
		if (list->type == SEP)
		{
			if (!list->next)
			{
				if (list->prev)
					list->prev->next = NULL;
				free(list->value);
				free(list);
				break ;
			}
			else if (list->index == 0)
				list = index_first(list);
			else
				list = removee(list);
		}
		if (!list->next)
			break ;
		list = list->next;
	}
	while (list->prev)
		list = list->prev;
	return (list);
}

char	*delete_sep(char *str, char *result)
{
	int (i) = 0;
	int (j) = 0;
	int (is_space) = 0;
	result = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
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
		else
			i++;
	}
	free(str);
	result[j] = '\0';
	return (result);
}
