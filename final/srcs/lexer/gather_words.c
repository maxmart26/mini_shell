/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:01:46 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/06 18:24:19 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"


void	list_gathering(t_data *tools)
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
