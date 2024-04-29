/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:54:00 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/29 17:00:11 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	env_var_expand(t_data *tools)
{
	t_token	*tmp;
	char	*str;

	str = NULL;
	tmp = tools->lexer_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			break ;
		else if (tmp->type == WORD)
		{
			if (ft_strnstr(tmp->value, "$?", 2))
			{
				tmp->value = replace_exit_status(tmp->value, tools, 0, NULL);
			}
			else if (tmp->value[0] != '\'' && tmp->value[0] != '\\'
				&& is_env_var(tmp->value, tools, NULL) == 1)
				tmp->value = replace_env_var(tmp->value, tools);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
