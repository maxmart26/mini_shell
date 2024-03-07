/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:58:16 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/03/07 18:04:00 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*find_env_var(char *str, t_env *env)
{
	while (env->next)
	{
		if (ft_strncmp(str, env->name, ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen(env->name))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

char	*is_still_env_var(char *str, t_data *tools)
{
	char	*result;
	int		i;
	int		start;

	i = 0;
	result = NULL;
	while (str[i] && str[i] != '$')
	{
		i++;
	}
	if (i > 0)
		result = ft_strjoin(result, ft_substr(str, 0, i));
	if (str[i] == '$')
	{
		i++;
		start = i;
		while ((str[i] > 'A' && str[i] < 'Z') || str[i] == '_')
			i++;
		if (find_env_var(ft_substr(str, start, i - start), tools->env))
			result = ft_strjoin(result,
					find_env_var(ft_substr(str, start, i - start), tools->env));
	}
	if (!ft_substr(str, i, ft_strlen(str) - i))
		return (result);
	return (ft_strjoin(result, ft_substr(str, i, ft_strlen(str) - i)));
}

char	*replace_env_var(char *str, t_data *tools)
{
	char	*value;

	value = NULL;
	value = is_still_env_var(str, tools);
	while (is_env_var(value) == 1)
		value = is_still_env_var(value, tools);
	return (value);
}

void	env_var_expand(t_data *tools)
{
	t_token	*tmp;

	tmp = tools->lexer_list;
	while (tmp->next)
	{
		if (tmp->type == WORD)
		{
			if (tmp->value[0] != '\'' && is_env_var(tmp->value) == 1)
				tmp->value = replace_env_var(tmp->value, tools);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
