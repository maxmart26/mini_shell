/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:04:37 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/10 13:33:25 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	check_error_newline(t_token *tmp)
{
	if (((tmp->type == GREAT || tmp->type == LESS || tmp->type == APPEND
				|| tmp->type == HEREDOC) && tmp->next->type == NEWL)
		|| (tmp->type == LESS && tmp->next->type == GREAT))
	{
		printf(SYNTAX_ERR);
		g_status = 258;
		return (1);
	}
	return (0);
}

int	check_error_pipe(t_token *tmp)
{
	if ((tmp->type == HEREDOC && tmp->next->type == PIPE)
		|| (tmp->type == APPEND && tmp->next->type == PIPE))
	{
		printf(SYNTAX_ERR);
		g_status = 258;
		return (1);
	}
	return (0);
}

int	check_syntax(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (!tmp)
		return (0);
	if ((tmp->type == HEREDOC && (tmp->next->type == GREAT
				|| tmp->next->type == LESS || tmp->next->type == APPEND
				|| tmp->next->type == HEREDOC)) || (tmp->type == APPEND
			&& (tmp->next->type == APPEND || tmp->next->type == LESS
				|| tmp->next->type == GREAT || tmp->next->type == HEREDOC)))
	{
		printf(SYNTAX_ERR);
		g_status = 258;
		return (printf("%s'\n", tmp->value), 1);
	}
	else if ((tmp->type == GREAT && tmp->next->type == GREAT)
		|| (tmp->type == LESS && tmp->next->type == LESS))
	{
		printf(SYNTAX_ERR);
		g_status = 258;
		return (printf("%s'\n", tmp->value), 1);
	}
	else if (check_error_pipe(tmp))
		return (printf("%s'\n", "|"), 1);
	return (0);
}

int	ft_verif_pipe(t_token *token)
{
	int(i) = 0;
	if (token->type == PIPE)
		token = token->next;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			i++;
		if (token->type == GREAT || token->type == LESS
			|| token->type == HEREDOC || token->type == APPEND)
			i--;
		token = token->next;
	}
	if (i > 0)
		return (0);
	else
		return (1);
}

int	first_check(t_token *tmp)
{
	if ((tmp->type == HEREDOC && (tmp->next && (tmp->next->type == GREAT
					|| tmp->next->type == LESS || tmp->next->type == APPEND
					|| tmp->next->type == HEREDOC))) || (tmp->type == APPEND
			&& (tmp->next && (tmp->next->type == APPEND
					|| tmp->next->type == LESS || tmp->next->type == GREAT
					|| tmp->next->type == HEREDOC))))
	{
		printf(SYNTAX_ERR);
		g_status = 258;
		return (printf("%s'\n", tmp->value), 1);
	}
	else if ((tmp->type == GREAT && (tmp->next && (tmp->next->type == GREAT
				|| tmp->next->type == HEREDOC || tmp->next->type == APPEND
				|| tmp->next->type == LESS))) || (tmp->type == LESS
			&& (tmp->next && (tmp->next->type == LESS || tmp->next->type == HEREDOC
				|| tmp->next->type == APPEND || tmp->next->type == GREAT))))
	{
		printf(SYNTAX_ERR);
		g_status = 258;
		return (printf("%s'\n", tmp->value), 1);
	}
	return (0);
}
