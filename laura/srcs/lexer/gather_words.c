/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:01:46 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/29 18:15:33 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	list_gathering(t_tools *tools)
{
	t_token	*token;
	t_token	*tmp;
	t_token	*result;
	char	*str;

	token = tools->lexer_list;
	result = token;
	while (token)
	{
		if (token->next)
		{
			if (token->type == WORD && token->next->type == WORD)
			{
				token->value = ft_strjoin(token->value, " ");
				str = token->value;
				token->value = ft_strjoin(token->value, token->next->value);
				free(str);
				tmp = token->next;
				token->next = token->next->next;
				token->next->prev = token;
				free(tmp);
			}
			else
			{
				tmp = token->next;
				token = tmp;
			}
		}
		else
		{
			tmp = token->next;
			token = tmp;
		}
	}
}
