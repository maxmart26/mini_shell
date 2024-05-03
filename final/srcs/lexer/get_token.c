/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:05:11 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/03 18:29:17 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

static void	token_not_pipe_semi(t_token *token_list, char *str, int *i, int *j)
{
	int		index;
	char	*token;

	char *(g_tab)[] = {"<<", ">>", ">", "<", "|", NULL};
	index = 0;
	while (g_tab[index] && ft_strncmp(str + *i, g_tab[index],
			ft_strlen(g_tab[index])))
		index++;
	if (g_tab[index] == NULL)
		return ;
	token = ft_strdup(g_tab[index]);
	add_token(token_list, index, token, *j);
	*i = *i + ft_strlen(g_tab[index]);
	free(token);
	(*j)++;
}

void	get_token(t_token *token_list, char *str, int *i, int *j)
{
	if (str[*i] == '|' && str[*i + 1] == '|')
	{
		add_token(token_list, PIPE, "||", *j);
		(*j)++;
		(*i) += 2;
	}
	else if (str[*i] == ';')
	{
		add_token(token_list, SEMI, ";", *j);
		(*j)++;
		(*i)++;
	}
	else
		token_not_pipe_semi(token_list, str, i, j);
}
