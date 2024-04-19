/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:35:30 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/16 14:49:06 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*other_type(t_token *list, char *type)
{
	if (list->type == NONE)
		type = "NONE";
	else if (list->type == NEWL)
		type = "NEWL";
	else if (list->type == CMD)
		type = "CMD";
	else if (list->type == SEMI)
		type = "SEMI";
	else if (list->type == ARG)
		type = "ARG";
	else if (list->type == CMD_BULT)
		type = "CMD_BULT";
	else if (list->type == APPEND)
		type = "APPEND";
	else if (list->type == OPT)
		type = "OPT";
	else
		type = "NONE";
	return (type);
}

char	*what_type(t_token *list)
{
	char	*type;
	t_token	*tmp;

	type = NULL;
	tmp = list;
	if (tmp->type == HEREDOC)
		type = "HEREDOC";
	else if (tmp->type == GREAT)
		type = "GREAT";
	else if (tmp->type == LESS)
		type = "LESS";
	else if (tmp->type == PIPE)
		type = "PIPE";
	else if (tmp->type == S_QUOTE)
		type = "S_QUOTE";
	else if (tmp->type == D_QUOTE)
		type = "D_QUOTE";
	else if (tmp->type == WORD)
		type = "WORD";
	else if (tmp->type == SEP)
		type = "SEP";
	else
		type = other_type(list, type);
	return (type);
}

void	ft_print_lexer(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("  \033[38;5;214m%d :\033[0m \
			\033[0;92m[%s]\033[0m \033[0;91m[%s]\033[0m\n",
			tmp->index, what_type(tmp), tmp->value);
		tmp = tmp->next;
	}
	printf("%c", '\n');
}
