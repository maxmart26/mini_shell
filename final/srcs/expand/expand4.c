/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:48:21 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/05/07 11:50:25 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*expand_env_var(char *str, int *i, char *result, t_data *tools)
{
	char	*expanded;
	char	*tmp;
	char	*exit_status;

	expanded = NULL;
	if (str[*i + 1] == '?')
	{
		if (*i == 0 || ((*i != 0) && str[*i - 1] != '$'))
		{
			exit_status = ft_itoa(tools->exit);
			expanded = expand_exit_status(i, &result, exit_status);
			free(exit_status);
		}
	}
	else if (is_env_var(str + *i, tools, NULL))
	{
		tmp = env_var(str + *i, tools);
		expanded = replace_env_var(str, i, &result, &tmp);
	}
	else
		expanded = skip_non_env_var(str, i, &result, 0);
	return (expanded);
}

char	*expand_exit_status(int *i, char **expanded, char *exit_status)
{
	char	*tmp1;
	char	*tmp;

	tmp = exit_status;
	tmp1 = *expanded;
	*expanded = ft_strjoin(*expanded, tmp);
	free(tmp1);
	*i += 2;
	return (*expanded);
}

char	*env_var(char *str, t_data *tools)
{
	char *(find_var) = NULL;
	int (start) = 0;
	int (i) = 0;
	char *(result) = NULL;
	if (str[i] == '$' && str[i + 1])
	{
		i++;
		start = i;
		while (ft_isalpha(str[i]) || str[i] == '_')
			i++;
		find_var = find_var_env(str, start, i, tools);
	}
	else if (str[i] == '$' && !str[i + 1])
		return (only_dollar(result));
	return (find_var);
}

char	*replace_env_var(char *line, int *i, char **result, char **tmp)
{
	char	*tmp1;

	tmp1 = *result;
	*result = ft_strjoin(*result, *tmp);
	if (tmp1)
		free(tmp1);
	if (line[*i] == '$')
		(*i)++;
	if (line[*i] == '_')
		(*i)++;
	else
	{
		while (ft_isalpha(line[*i]) || ft_isalnum(line[*i]) || line[*i] == '_')
			(*i)++;
	}
	return (*result);
}

int	check_end_of_string(char str, int inside_quotes)
{
	if (inside_quotes == 0)
	{
		if (!str)
			return (1);
	}
	else
	{
		if (str == '\"')
			return (1);
	}
	return (0);
}
