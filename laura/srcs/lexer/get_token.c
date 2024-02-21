/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:05:11 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/02/21 15:34:54 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static const char *const g_tab[] = {"<<", ">>", ">", "<", "|", NULL};

static void	token_not_pipe_semi(t_token *token_list, char *str, int *i, int *j)
{
	int	index;

	index = 0;
	while (g_tab[index] && ft_strncmp(str + *i, g_tab[index],
			ft_strlen(g_tab[index])))
		index++;
	if (g_tab[index] == NULL)
		return ;
	add_token(token_list, index, ft_strdup(g_tab[index]), *j);
	*i = *i + ft_strlen(g_tab[index]);
	(*j)++;
}

void	get_token(t_token *token_list, char *str, int *i, int *j)
{
	if (str[*i] == '|' && str[*i + 1] == '|')
	{
		add_token(token_list, PIPE, ft_strdup("||"), *j);
		(*j)++;
		(*i) += 2;
	}
	else if (str[*i] == ';')
	{
		add_token(token_list, SEMI, ft_strdup(";"), *j);
		(*j)++;
		(*i)++;
	}
	else
		token_not_pipe_semi(token_list, str, i, j);
}
