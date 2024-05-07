/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:42:27 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/07 16:35:24 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

t_token	*first_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->index = 0;
	new_token->next = NULL;
	new_token->type = NONE;
	new_token->value = ft_strdup("NONE");
	new_token->str = NULL;
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
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
	if (!tmp->next)
		return ;
	tmp->next->index = i;
	tmp->next->type = type;
	tmp->next->value = ft_strdup(str);
	tmp->next->str = NULL;
	if (!tmp->next->value)
	{
		free(tmp->next->value);
		free(tmp->next);
		free(str);
		return ;
	}
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
}

void	destroy_str(t_token *token_list)
{
	t_token	*tmp;
	t_token	*next_node;

	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == WORD)
			ft_free_tab(tmp->str);
		next_node = tmp->next;
		tmp = next_node;
	}
}

void	destroy_token_list(t_token *token_list)
{
	t_token	*tmp;
	t_token	*next_node;

	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (tmp->str != NULL)
				ft_free_tab(tmp->str);
		}
		next_node = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next_node;
	}
}
