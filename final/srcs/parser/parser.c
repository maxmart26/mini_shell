/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:42:44 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/22 12:11:20 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

int	check_error_newline(t_data *tools, t_token *tmp)
{
	if (((tmp->type == GREAT || tmp->type == LESS || tmp->type == APPEND
				|| tmp->type == HEREDOC) && tmp->next->type == NEWL)
		|| (tmp->type == LESS && tmp->next->type == GREAT))
	{
		printf(SYNTAX_ERR);
		tools->exit_status = 258;
		return (1);
	}
	return (0);
}

int	check_error_pipe(t_data *tools, t_token *tmp)
{
	if ((tmp->type == HEREDOC && tmp->next->type == PIPE)
		|| (tmp->type == APPEND && tmp->next->type == PIPE))
	{
		printf(SYNTAX_ERR);
		tools->exit_status = 258;
		return (1);
	}
	return (0);
}

int	check_syntax(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (check_error_newline(tools, tmp))
		return (printf("%s'\n", "newline"), 1);
	if ((tmp->type == HEREDOC && (tmp->next->type == GREAT
				|| tmp->next->type == HEREDOC)) || (tmp->type == APPEND
			&& (tmp->next->type == APPEND || tmp->next->type == LESS)))
	{
		printf(SYNTAX_ERR);
		tools->exit_status = 258;
		return (printf("%s'\n", tmp->value), 1);
	}
	else if ((tmp->type == GREAT && tmp->next->type == GREAT)
		|| (tmp->type == LESS && tmp->next->type == LESS))
	{
		printf(SYNTAX_ERR);
		tools->exit_status = 258;
		return (printf("%s'\n", tmp->value), 1);
	}
	else if (check_error_pipe(tools, tmp))
		return (printf("%s'\n", "|"), 1);
	return (0);
}

int	check_dir(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if ((strncmp(tmp->value, "/", 1) == 0 || strncmp(tmp->value, ".", 1) == 0)
		&& tmp->next->type == NEWL)
	{
		printf("%s %s", "bash: ", tmp->value);
		tools->exit_status = 258;
		return (printf(DIR_ERR), 1);
	}
	else if ((strncmp(tmp->value, "\\", 1) == 0 || strncmp(tmp->value, "-",
				1) == 0) && tmp->next->type == NEWL)
	{
		printf("%s %s", "bash: ", tmp->value);
		tools->exit_status = 258;
		return (printf(CMD_ERR), 1);
	}
	else if (strncmp(tmp->value, "|", 1) == 0)
	{
		printf(SYNTAX_ERR);
		tools->exit_status = 258;
		return (printf("%s'\n", tmp->value), 1);
	}
	return (0);
}

int	check_spe_char(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (strncmp(tmp->value, "&", 1) == 0)
	{
		printf(SYNTAX_ERR);
		tools->exit_status = 258;
		return (printf("%s'\n", "&&"), 1);
	}
	else if (tmp->type == SEMI)
	{
		printf(SYNTAX_ERR);
		tools->exit_status = 258;
		return (printf("%s'\n", ";;"), 1);
	}
	return (0);
}

int	check_word_only(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (tmp->type == WORD && tmp->next->type == NEWL)
	{
		printf("%s %s", "bash: ", tmp->value);
		tools->exit_status = 258;
		return (printf(CMD_ERR), 1);
	}
	return (0);
}

void	parsing(t_data *tools)
{
	if (check_syntax(tools))
		return ;
	if (check_dir(tools))
		return ;
	if (check_spe_char(tools))
		return ;
	if (check_word_only(tools))
		return ;
}
