/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:58:16 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/09 12:15:06 by lnunez-t         ###   ########.fr       */
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
	char	*env_var;
	char	*find_var;
	int		i;
	int		start;
	char	*tmp;
	char	*tmp_result;

	i = 0;
	result = NULL;
	while (str[i] && str[i] != '$')
	{
		i++;
	}
	if (i > 0)
	{
		tmp = ft_substr(str, 0, i);
		result = tmp;
	}
	if (str[i] == '$')
	{
		i++;
		start = i;
		while ((str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
			i++;
		env_var = ft_substr(str, start, i - start);
		find_var = find_env_var(env_var, tools->env);
		free(env_var);
		if (find_var)
		{
			tmp = ft_strjoin(result, find_var);
			free(result);
			result = tmp;
		}
	}
	tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (!tmp)
		return (result);
	tmp_result = ft_strjoin(result, tmp);
	free(result);
	free(tmp);
	return (tmp_result);
}

char	*replace_env_var(char *str, t_data *tools)
{
	char	*value;

	value = NULL;
	value = is_still_env_var(str, tools);
	while (is_env_var(value, tools) == 1)
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
			if (tmp->value[0] != '\'' && is_env_var(tmp->value, tools) == 1)
				tmp->value = replace_env_var(tmp->value, tools);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
