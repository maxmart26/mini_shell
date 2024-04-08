/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:08:14 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/07 12:10:45 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*delete_quotes(char *str)
{
	char	*result;
	char	**cut;
	int		i;

	result = NULL;
	i = 0;
	cut = malloc(sizeof(char) * (ft_strlen(str) - 2));
	if (!cut)
		return (NULL);
	if (which_quote(str) == 1)
		cut = ft_split(str, '\"');
	else if (which_quote(str) == 2)
		cut = ft_split(str, '\'');
	while (cut[i])
	{
		result = ft_strjoin(result, cut[i]);
		i++;
	}
	return (result);
}

void	remove_quotes(t_token *lexer_list)
{
	t_token	*tmp;

	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			while (quote_in_str(tmp->value) == 1)
			{
				tmp->value = delete_quotes(tmp->value);
			}
			tmp->value = delete_sep(tmp->value);
		}
		tmp = tmp->next;
	}
}