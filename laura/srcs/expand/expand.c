/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:58:16 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/06 18:00:53 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*replace_env_var(char *str)
{
	char	*result;
	char	*copy;
	char	*var;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	result = NULL;
	while (str[i] && str[i] != '$')
	{
		end++;
		i++;
	}
	if (end > 0)
	{
		var = ft_substr(str, start, end);
		result = ft_strjoin(result, var);
	}
	start = i;
	end = 0;
	if (str[i] == '$')
	{
		while ((str[i] > 'A' && str[i] < 'Z') || str[i] == '_')
		{
			end++;
			i++;
		}
		var = ft_substr(str, start + 1, end);
		//ajouter fonction qui va chercher la var environnememt
	}
	if (str[i] == '\0')
		return (result);
	copy = ft_substr(str, i, ft_strlen(str) - i);
	if (is_env_var(copy) == 1)
		replace_env_var(copy);
	result = ft_strjoin(result, copy);
	return (result);
}

void	env_var_expand(t_tools *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	while (tmp->next)
	{
		if (tmp->type == WORD)
		{
			if (tmp->value[0] != '\'' && is_env_var(tmp->value) == 1)
				tmp->value = replace_env_var(tmp->value);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
