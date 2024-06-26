/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:14:38 by matorgue          #+#    #+#             */
/*   Updated: 2024/03/25 15:25:02 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

t_token	*token_init(char *str, char *st)
{
	t_token	*token;
	t_token	*tmp;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = str;
	token->next = init_token(token);
	tmp = token->next;
	token = tmp;
	token->value = st;
	tmp = token->prev;
	token = tmp;
	return (tmp);
}
