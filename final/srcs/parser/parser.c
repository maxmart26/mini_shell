/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:42:44 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/06 18:24:19 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"


/*t_parser	init_parser(t_token *list, t_data *tools)
{
	t_parser	parser_tools;

	parser_tools.lexer_list = list;
	parser_tools.nb_redirs = 0;
	parser_tools.redirs = NULL;
	parser_tools.tools = tools;
	return (parser_tools);
}

void	parser(t_data *tools)
{
	t_parser	parser_tools;

	count_pipes(tools->lexer_list, tools);
	while (tools->lexer_list)
	{
		parser_tools = init_parser(tools->lexer_list, tools);
		//body
		tools->lexer_list = parser_tools.lexer_list;
	}
	return (EXIT_SUCCESS);
}*/
