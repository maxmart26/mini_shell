/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:42:44 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/01 16:19:22 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*only_dollar(char *result)
{
	char	*tmp_result;

	tmp_result = "$";
	if (result)
		free(result);
	return (tmp_result);
}

/*char	*replace_env_var(char *str, t_data *tools)
{
	char	*value;

	value = NULL;
	value = is_still_env_var(str, tools, NULL);
	free(str);
	while (is_env_var(value, tools, NULL) == 1)
	{
		value = is_still_env_var(value, tools, NULL);
	}
	return (value);
}*/

char	*replace_exit_status(char *str, t_data *tools, int i, char *tmp)
{
	int (j) = 0;
	char *(result) = NULL;
	while (str[i] && str[i] != '$')
		i++;
	if (i > 0)
	{
		tmp = ft_substr(str, 0, i);
		result = tmp;
	}
	if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] == '?')
	{
		result = display_exit_status(tools, result);
		i++;
	}
	if (str[i + 1])
	{
		j = i;
		while (str[j])
			j++;
		free(tmp);
		j--;
		check_after_exit_status(str, j, result, i);
	}
	free(str);
	return (result);
}

char	*check_after_exit_status(char *str, int j, char *result, int i)
{
	char	*tmp;

	tmp = NULL;
	if (str[j])
	{
		tmp = ft_substr(str, i + 1, j - i + 1);
		result = ft_strjoin(result, tmp);
		free(tmp);
	}
	return (result);
}

char	*display_exit_status(t_data *tools, char *result)
{
	char	*exit_status;
	char	*tmp;

	exit_status = ft_itoa(tools->exit);
	tmp = ft_strjoin(result, exit_status);
	free(exit_status);
	free(result);
	return (tmp);
}
