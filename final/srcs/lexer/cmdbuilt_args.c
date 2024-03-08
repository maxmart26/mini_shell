/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdbuilt_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:44:17 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/08 18:13:24 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	add_cd_args(t_token *token)
{
	if (token->next->type == WORD)
		token->next->type = ARG;
}

void	add_echo_args(t_token *token)
{
	while (token->next->type == WORD)
	{
		token->next->type = ARG;
		token = token->next;
	}
}

void	add_exp_args(t_token *token)
{
	while (token->next->type == WORD)
	{
		token->next->type = ARG;
		token = token->next;
	}
}

void	add_unset_args(t_token *token)
{
	while (token->next->type == WORD)
	{
		token->next->type = ARG;
		token = token->next;
	}
}
