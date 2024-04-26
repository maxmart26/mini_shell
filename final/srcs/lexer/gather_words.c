/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:01:46 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/26 14:22:24 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

t_token	*consecutive_words(t_token *token)
{
	char	*str;
	char	*concat;
	t_token	*tmp;

	str = ft_strjoin(token->value, " ");
	concat = ft_strjoin(str, token->next->value);
	free(token->value);
	free(str);
	token->value = concat;
	tmp = token->next;
	if (tmp->next)
	{
		token->next = tmp->next;
		token->next->prev = token;
		free(tmp->value);
		free(tmp);
	}
	else
		token->next = NULL;
	return (token);
}

void	list_gathering(t_data *tools)
{
	t_token	*token;
	t_token	*tmp;
	t_token	*result;

	token = tools->lexer_list;
	result = token;
	while (token)
	{
		if (token->next)
		{
			if (token->next && token->type == WORD && token->next->type == WORD)
				token = consecutive_words(token);
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
