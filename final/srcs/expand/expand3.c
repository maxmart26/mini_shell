/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:54:00 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/05 16:51:50 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	env_var_expand(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			break ;
		else if (tmp->type == WORD)
			tmp->value = expand_word(tmp->value, tools);
		tmp = tmp->next;
	}
}

char	*expand_word(char *str, t_data *tools)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '\\')
			expand_backslash(str, &i, &result);
		else if (str[i] == '\'')
			remove_sq(str, &i, &result);
		else if (str[i] == '\"')
			result = expand_dq(str, &i, result, tools);
		else if (str[i] == '$')
			result = expand_env_var(str, &i, result, tools);
		else
			get_char(str, &i, &result);
	}
	free(str);
	return (result);
}

void	expand_backslash(char *str, int *i, char **result)
{
	int		j;
	char	*tmp1;
	char	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	j = *i;
	while (str[j] == '\\')
	{
		tmp1 = *result;
		tmp = ft_substr(str, j + 1, 1);
		*result = ft_strjoin(*result, tmp);
		free(tmp1);
		free(tmp);
		j += 2;
	}
	*i = j;
}

void	remove_sq(char *str, int *i, char **result)
{
	int		j;
	char	*tmp1;
	char	*tmp;

	(*i)++;
	j = *i;
	while (str[j] != '\'')
		j++;
	tmp1 = *result;
	tmp = ft_substr(str, *i, j - *i);
	if (tmp)
	{
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		free(tmp1);
	}
	*i = j + 1;
}

void	get_char(char *str, int *i, char **result)
{
	char	*tmp1;
	char	*tmp;

	tmp1 = *result;
	tmp = ft_substr(str, *i, 1);
	*result = ft_strjoin(*result, tmp);
	free(tmp1);
	free(tmp);
	(*i)++;
}
