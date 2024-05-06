/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:12:40 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/06 17:13:06 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

t_token	*lexer(char *str)
{
	t_token	*token_list;

	token_list = NULL;
	token_list = first_token();
	fill_token_list(token_list, str);
	return (token_list);
}
