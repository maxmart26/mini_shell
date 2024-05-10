/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:07:02 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/10 07:26:29 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	delete_null_token(t_data *tools)
{
	t_token	*token;
	t_token	*tmp;

	token = tools->lexer_list;
	while (token)
	{
		if (token->next && token->next->value == NULL)
		{
			tmp = token->next;
			token->next = token->next->next;
			if (token->next != NULL)
				token->next->prev = token;
			if (tmp->str)
				ft_free_tab(tmp->str);
			free(tmp);
		}
		token = token->next;
	}
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

int	check_null_list(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if ((!tmp && g_status != 6 && g_status != 5) || (tmp && !tmp->value))
	{
		if (tmp && !tmp->value)
		{
			tools->exit = 127;
			ft_printf_error("bash: command not found\n");
		}
		g_status = 258;
		return (1);
	}
	return (0);
}

int	check_dir(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	if (tmp && tmp->type == WORD && ft_strncmp(tmp->value, ".",
			ft_strlen(tmp->value)) == 0 && !tmp->next)
	{
		g_status = 258;
		ft_printf_error("bash: .: filename argument required\n");
		return (1);
	}
	else
		return (0);
}

void	parsing(t_data *tools)
{
	if (check_syntax(tools))
		return ;
	if (check_spe_char(tools))
		return ;
	if (check_null_list(tools))
		return ;
	if (check_dir(tools))
		return ;
}
