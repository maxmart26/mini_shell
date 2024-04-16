/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:58:16 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/16 17:08:28 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*find_env_var(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(str, env->value, ft_strlen(str) - 1) == 0
			&& env->value[ft_strlen(str)] == '=')
			return (&env->value[ft_strlen(str) + 1]);
		env = env->next;
	}
	return (NULL);
}

char	*is_still_env_var(char *var, t_data *tools)
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
	while (var[i] && var[i] != '$')
	{
		i++;
	}
	if (i > 0)
	{
		tmp = ft_substr(var, 0, i);
		result = tmp;
	}
	if (var[i] == '$' && var[i + 1])
	{
		i++;
		start = i;
		while ((var[i] >= 'A' && var[i] <= 'Z') || var[i] == '_')
			i++;
		env_var = ft_substr(var, start, i - start);
		find_var = find_env_var(env_var, tools->env);
		free(env_var);
		if (find_var)
		{
			tmp = ft_strjoin(result, find_var);
			if (result)
				free(result);
			result = tmp;
		}
	}
	else if (var[i] == '$' && !var[i + 1])
	{
		tmp_result = "$";
		if (result)
			free(result);
		return (tmp_result);
	}
	tmp = ft_substr(var, i, ft_strlen(var) - i);
	if (!tmp)
		return (result);
	tmp_result = ft_strjoin(result, tmp);
	if (result)
		free(result);
	free(tmp);
	if (find_var)
		free(find_var);
	return (tmp_result);
}

char	*replace_env_var(char *str, t_data *tools)
{
	char	*value;

	value = NULL;
	value = is_still_env_var(str, tools);
	while (is_env_var(value, tools) == 1)
	{
		value = is_still_env_var(value, tools);
	}
	return (value);
}

void	env_var_expand(t_data *tools)
{
	t_token	*tmp;
	char	*str;

	str = NULL;
	tmp = tools->lexer_list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (tmp->value[0] != '\'' && tmp->value[0] != '\\'
				&& is_env_var(tmp->value, tools) == 1)
				tmp->value = replace_env_var(tmp->value, tools);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
