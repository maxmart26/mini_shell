/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:22:28 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/01 19:21:57 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

void	expand_backslash_dq(char *str, int *i, char **result)
{
	int		j;
	char	*tmp1;
	char	*tmp;

	j = *i;
	if (ft_strchr("$\"\\\n`", str[j + 1]))
	{
		tmp = *result;
		tmp1 = ft_substr(str, j + 1, 1);
		*result = ft_strjoin(*result, tmp1);
		j += 2;
		free(tmp);
		free(tmp1);
	}
	else
	{
		tmp = *result;
		tmp1 = ft_substr(str, j, 2);
		*result = ft_strjoin(*result, tmp1);
		j += 2;
		free(tmp);
		free(tmp1);
	}
	*i = j;
}

char	*expand_env_var_dq(char *line, char *result, int *j,
		t_data *tools)
{
	char	*expanded;
	char	*tmp;

	expanded = NULL;
	if (is_env_var(line + *j, tools, NULL))
	{
		tmp = env_var(line + *j, tools);
		expanded = replace_env_var(line, j, &result, &tmp);
	}
	else
		expanded = skip_non_env_var(line, j, &result, 1);
	return (expanded);
}

char	*remove_dq(char *str, int *i, t_data *tools)
{
	int		j;
	char	*result;
	char	*line;
	char	*exit_status;

	result = NULL;
	j = *i + 1;
	line = str;
	while (line[j] != '\"')
	{
		if (line[j] == '\\')
			expand_backslash_dq(line, &j, &result);
		else
		{
			if (line[j] == '$' && line[j - 1] != '$' && line[j + 1] == '?')
			{
				exit_status = ft_itoa(tools->exit);
				result = expand_exit_status(&j, &result, exit_status);
				free(exit_status);
			}
			else if (line[j] == '$')
				result = expand_env_var_dq(line, result, &j, tools);
			else
				get_char(line, &j, &result);
		}
	}
	j++;
	*i = j;
	return (result);
}

char	*expand_dq(char *str, int *i, char *result, t_data *tools)
{
	char	*tmp1;
	char	*tmp;

	tmp1 = result;
	tmp = remove_dq(str, i, tools);
	if (tmp)
	{
		result = ft_strjoin(result, tmp);
		//free(tmp);
		free(tmp1);
	}
	return (result);
}
