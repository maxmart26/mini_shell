/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:16:49 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/28 18:34:28 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_include.h"
#include "include/minishell_proto.h"
#include "include/minishell_struct.h"

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

int	main(int ac, char **av, char **env)
{
	t_token	*list;
	t_token	*tmp;
	char	*str;

	if (ac != 1)
		return (0);
	av[0] = NULL;
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
		ft_main(list, env);
	}
	return (0);
}
