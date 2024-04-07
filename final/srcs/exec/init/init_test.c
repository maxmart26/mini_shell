/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:53:44 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/07 14:07:24 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

void	init_test(t_token *token)
{
	t_token	*tmp;

	token->prev = NULL;
	token->index = 0;
	token->next = NULL;
	token->type = CMD_ABS;
	token->value = "/bin/ls";
	token->next = init_token(token);
	tmp = token->next;
	token = tmp;
	token->index = 1;
	token->type = ARG;
	token->value = "-a";
}

t_token	*init_token(t_token *prev)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->prev = prev;
	new->next = NULL;
	return (new);
}
