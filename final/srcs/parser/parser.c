/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:42:44 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/29 14:48:30 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	check_dir(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if ((strncmp(tmp->value, "/", 1) == 0 || strncmp(tmp->value, ".", 1) == 0)
		&& tmp->next->type == NEWL)
	{
		printf("%s %s", "bash: ", tmp->value);
		g_status = 258;
		return (printf(DIR_ERR), 1);
	}
	else if ((strncmp(tmp->value, "\\", 1) == 0 || strncmp(tmp->value, "-",
				1) == 0) && tmp->next->type == NEWL)
	{
		printf("%s %s", "bash: ", tmp->value);
		g_status = 258;
		return (printf(CMD_ERR), 1);
	}
	else if (strncmp(tmp->value, "|", 1) == 0)
	{
		printf(SYNTAX_ERR);
		g_status = 258;
		return (printf("%s'\n", tmp->value), 1);
	}
	return (0);
}

int	check_spe_char(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (!tmp)
		return (0);
	if (strncmp(tmp->value, "&", 1) == 0)
	{
		printf(SYNTAX_ERR);
		g_status = 258;
		return (printf("%s'\n", "&&"), 1);
	}
	else if (tmp->type == SEMI)
	{
		printf(SYNTAX_ERR);
		g_status = 258;
		return (printf("%s'\n", ";"), 1);
	}
	return (0);
}

int	check_word_only(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (tmp->type == WORD && tmp->next->type == NEWL)
	{
		printf("%s", "bash: ");
		first_word(tmp->value);
		g_status = 258;
		return (printf(CMD_ERR), 1);
	}
	return (0);
}

void	parsing(t_data *tools)
{
	if (check_syntax(tools))
		return ;
	if (check_spe_char(tools))
		return ;
}
