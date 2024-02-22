/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:16:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/22 15:50:39 by lnunez-t         ###   ########.fr       */
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
	t_token	*tmp;

	tmp = list;
	while (tmp->next)
	{
		printf("  %d : [%s] [%s]\n", tmp->index,
			what_type(tmp), tmp->value);
		tmp = tmp->next;
	}
	printf("%c", '\n');
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
		def_index(list);
		printf("\n%s\n\n", "Ind : [TYPE] [TOKEN]");
		ft_print_lexer(list);
	}
	return (0);
}
