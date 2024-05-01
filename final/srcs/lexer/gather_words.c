/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:01:46 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/01 13:49:23 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	list_gathering_next(t_token *token, char *str, t_token *tmp,
		char *concat)
{
	if (token->next && token->type == WORD && token->next->type == WORD)
	{
		str = ft_strjoin(token->value, " ");
		concat = ft_strjoin(str, token->next->value);
		free(token->value);
		free(str);
		token->value = concat;
		tmp = token->next;
		token->next = tmp->next;
		if (tmp->next)
			token->next->prev = token;
		free(tmp->value);
		free(tmp);
		return (0);
	}
	return (1);
}
int		len_str(t_token *token)
{
	int (i) = 0;

	while(token && token->type != PIPE && token->type != SEMI)
	{
		token = token->next;
		i++;
	}
	return (i);
}

void	test(t_data *tools)
{
	t_token *(token) = tools->lexer_list;
	t_token *(result) = NULL;
	int	(i) = 0;

	while (token)
	{
		i = 0;
		if (!token->prev || token->prev->type == PIPE || token->prev->type == SEMI)
		{
			token->str = (malloc((len_str(token) + 1) * sizeof(char *)));
			result = token;
			while (token && token->type != PIPE && token->type != SEMI)
			{
				result->str[i] = ft_strdup(token->value);
				i++;
				token = token->next;
			}
			result->str[i] = NULL;
		}
		else
			token = token->next;
	}
}
void	list_gathering(t_data *tools)
{
	t_token	*token;
	t_token	*tmp;

	char *(str) = NULL;
	char *(concat) = NULL;
	token = tools->lexer_list;
	test(tools);
	while (token)
	{
		if (token->next)
		{
			if (list_gathering_next(token, str, tmp, concat) == 1)
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
