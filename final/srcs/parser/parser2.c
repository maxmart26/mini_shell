/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:28:45 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/25 16:29:12 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

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
