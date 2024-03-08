/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:44:40 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/08 17:59:23 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	add_ls_args(t_token *token)
{
	while (token->next->type == WORD)
	{
		if (token->next->value[0] == '/' || token->next->value[0] == '~'
			|| token->next->value[0] == '.' || token->next->value[0] == '-')
			token->next->type = ARG;
		token = token->next;
	}
}

void	add_wc_args(t_token *token)
{
	while (token->next->type == WORD)
	{
		token->next->type = ARG;
		token = token->next;
	}
}

void	add_awk_args(t_token *token)
{
	while (token->next->type == WORD)
	{
		token->next->type = ARG;
		token = token->next;
	}
}

void	word_to_arg(t_token *token)
{
	token->next->type = ARG;
	token = token->next;
	while (token->next->type == WORD)
	{
		token->next->type = ARG;
		token = token->next;
	}
	if (token->next->type == PIPE)
	{
		token = token->next;
		if (ft_strncmp(token->next->value, "more", 4)
			&& ft_strlen(token->next->value) == 4)
			token->next->type = ARG;
	}
	else if (token->next->type == HEREDOC && token->next->next->type == WORD)
		token->next->next->type = ARG;
	else if (token->next->type == GREAT && token->next->next->type == WORD)
	{
		token = token->next;
		while (token->next->type == WORD)
		{
			token->next->type = ARG;
			token = token->next;
		}
	}
}

void	add_cat_args(t_token *token)
{
	if (token->next->type == GREAT && token->next->next->type == WORD)
		token->next->next->type = ARG;
	else if (token->next->type == WORD)
		word_to_arg(token);
}
