/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:58:16 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/15 17:44:40 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*find_env_var(char *str, t_env *env)
{
	while (env)
	{
		printf("%s\n", env->value);
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
			free(result);
			result = tmp;
		}
	}
	else if (var[i] == '$' && !var[i + 1])
	{
		tmp_result = "$";
		free(result);
		return (tmp_result);
	}
	tmp = ft_substr(var, i, ft_strlen(var) - i);
	if (!tmp)
		return (result);
	tmp_result = ft_strjoin(result, tmp);
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

	tmp = tools->lexer_list;
	printf("test\n");
	while (tmp)
	{
		printf("test1\n");
		if (tmp->type == WORD)
		{
			printf("test2\n");
			if (tmp->value[0] != '\'' && is_env_var(tmp->value, tools) == 1)
			{
				printf("test3\n");
				tmp->value = replace_env_var(tmp->value, tools);
			}
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
