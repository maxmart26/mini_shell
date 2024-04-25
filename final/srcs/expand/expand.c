/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:58:16 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/25 18:17:09 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*find_env_var(char *var, int i, int start, t_env *env)
{
	char	*env_var;

	env_var = ft_substr(var, start, i - start);
	free(env_var);
	while (env)
	{
		if (ft_strncmp(var, env->value, ft_strlen(var) - 1) == 0
			&& env->value[ft_strlen(var)] == '=')
			return (&env->value[ft_strlen(var) + 1]);
		env = env->next;
	}
	return (NULL);
}

char	*is_still_env_var(char *var, t_data *tools)
{
	int		start;
	char	*tmp;
	char	*find_var;

	int (i) = 0;
	char *(result) = NULL;
	while (var[i] && var[i] != '$')
		i++;
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
		find_var = find_env_var(var, i, start, tools->env);
		result = add_env_var(result, find_var);
	}
	else if (var[i] == '$' && !var[i + 1])
		return (is_empty_var(result));
	return (add_env_var_next(var, i, result));
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

char	*replace_exit_status(char *str, t_data *tools)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	result = NULL;
	while (str[i] && str[i] != '$')
		i++;
	if (i > 0)
	{
		tmp = ft_substr(str, 0, i);
		result = tmp;
	}
	if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] == '?')
	{
		result = ft_exit_status(tools);
		i++;
	}
	if (str[i + 1])
	{
		free(tmp);
		add_whats_next(str, i, result);
	}
	return (result);
}

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
			if (ft_strnstr(tmp->value, "$?", ft_strlen(tmp->value)))
			{
				tmp->value = replace_exit_status(tmp->value, tools);
			}
			if (tmp->value[0] != '\'' && tmp->value[0] != '\\'
				&& is_env_var(tmp->value, tools) == 1)
				tmp->value = replace_env_var(tmp->value, tools);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
