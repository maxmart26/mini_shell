/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:28:43 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/23 11:44:10 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	add_grep_args(t_token *token)
{
	while (token->next->type == WORD)
	{
		if (token->next->value[0] == '-')
			token->next->type = OPT;
		else
			token->next->type = ARG;
		token = token->next;
	}
}

/*void	add_tac_args(t_token *token)
{

}*/
