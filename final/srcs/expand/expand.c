/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:58:16 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/06 17:17:00 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*find_env_var(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(str, env->value, ft_strlen(str)) == 0
			&& env->value[ft_strlen(str)] == '=')
			return (&env->value[ft_strlen(str) + 1]);
		env = env->next;
	}
	return (NULL);
}

char	*is_still_env_var(char *var, t_data *tools, char *tmp)
{
	char *(find_var) = NULL;
	int (start) = 0;
	int (i) = 0;
	char *(result) = NULL;
	while (var[i] && var[i] != '$')
		i++;
	result = check_before_env_var(result, i, var);
	if (var[i] == '$' && var[i + 1])
	{
		i++;
		start = i;
		while (ft_isalpha(var[i]) || var[i] == '_')
			i++;
		find_var = find_var_env(var, start, i, tools);
		if (find_var)
		{
			tmp = ft_strjoin(result, find_var);
			if (result)
				free(result);
			result = tmp;
		}
	}
	else if (var[i] == '$' && !var[i + 1])
		return (only_dollar(result));
	return (print_result(tmp, result, var, i));
}

char	*check_before_env_var(char *result, int i, char *var)
{
	char	*tmp;

	if (i > 0)
	{
		tmp = ft_substr(var, 0, i);
		result = tmp;
	}
	return (result);
}

char	*find_var_env(char *var, int start, int i, t_data *tools)
{
	char	*env_var;
	char	*find_var;

	env_var = ft_substr(var, start, i - start);
	find_var = find_env_var(env_var, tools->env);
	free(env_var);
	return (find_var);
}

char	*print_result(char *tmp, char *result, char *var, int i)
{
	char	*tmp_result;

	tmp = ft_substr(var, i, ft_strlen(var) - i);
	if (!tmp)
		return (result);
	tmp_result = ft_strjoin(result, tmp);
	if (result)
		free(result);
	free(tmp);
	return (tmp_result);
}
