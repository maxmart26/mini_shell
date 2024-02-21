/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:16:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/21 18:04:36 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"

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
	else
		type = "NONE";
	return (type);
}

char	*what_type(t_token *list)
{
	char	*type;

	type = NULL;
	if (list->type == HEREDOC)
		type = "HEREDOC";
	else if (list->type == APPEND)
		type = "APPEND";
	else if (list->type == GREAT)
		type = "GREAT";
	else if (list->type == LESS)
		type = "LESS";
	else if (list->type == PIPE)
		type = "PIPE";
	else if (list->type == S_QUOTE)
		type = "S_QUOTE";
	else if (list->type == D_QUOTE)
		type = "D_QUOTE";
	else if (list->type == WORD)
		type = "WORD";
	else if (list->type == SEP)
		type = "SEP";
	else
		other_type(list, type);
	return (type);
}

void	ft_print_lexer(t_token *list)
{
	while (list->next)
	{
		printf("%d : [%s] [%s]\n", list->index,
			what_type(list), list->value);
		list = list->next;
	}
}

int	main(void)
{
	t_token	*list;
	t_token	*tmp;
	char	*str;

	while (1)
	{
		str = readline("matorgue:~$ ");
		list = lexer(str);
		tmp = list->next;
		free(list);
		list = tmp;
		list = remove_sep(list);
		ft_print_lexer(list);
	}
	return (0);
}
