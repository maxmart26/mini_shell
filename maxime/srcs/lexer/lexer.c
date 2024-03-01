/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:42:27 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/28 19:09:31 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

t_token	*first_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->index = 0;
	new_token->next = NULL;
	new_token->type = NONE;
	new_token->value = ft_strdup("NONE");
	new_token->prev = NULL;
	return (new_token);
}

void	add_token(t_token *token_list, t_token_type type, char *str, int i)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_token *)malloc(sizeof(t_token));
	tmp->next->index = i;
	tmp->next->type = type;
	tmp->next->value = str;
	tmp->next->next = NULL;
	tmp->next->prev = tmp;
}

void	fill_token_list(t_token *token_list, char *str)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			add_token(token_list, SEP, " ", index);
			i++;
			index++;
		}
		else if (ft_strrchr("|><;", str[i]))
			get_token(token_list, str, &i, &index);
		else if (!ft_strrchr("\t |<>;", str[i]) || str[i] == '\\')
			get_word(token_list, str, &i, &index);
		else
			i++;
	}
	add_token(token_list, NEWL, "newline", index);
}

void	destroy_token_list(t_token *token_list)
{
	t_token	*tmp;

	tmp = NULL;
	while (token_list->type != NEWL)
	{
		tmp = token_list;
		token_list = token_list->next;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
	if (token_list->type == NEWL)
	{
		free(token_list->value);
		token_list->value = NULL;
		free(token_list);
		token_list = NULL;
	}
}

t_token	*lexer(char *str)
{
	t_token	*token_list;

	token_list = NULL;
	token_list = first_token();
	fill_token_list(token_list, str);
	//printf("test9\n");
	return (token_list);
}
