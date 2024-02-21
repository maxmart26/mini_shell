/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:55:48 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/21 18:03:29 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*remove_sep(t_token *list)
{
	t_token	*tmp;
	t_token	*result;

	tmp = list;
	result = NULL;
	while (tmp->next)
	{
		if (tmp->type != SEP)
		{
			result = tmp;
			result = result->next;
		}
		tmp = tmp->next;
	}
	return (result);
}
