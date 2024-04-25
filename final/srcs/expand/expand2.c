/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:44:25 by lnunez-t          #+#    #+#             */
/*   Updated: 2024/04/25 18:14:07 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_include.h"
#include "../../include/minishell_proto.h"
#include "../../include/minishell_struct.h"

char	*ft_exit_status(t_data *tools)
{
	char	*exit_status;
	char	*result;

	result = NULL;
	exit_status = ft_itoa(tools->exit);
	result = ft_strjoin(result, exit_status);
	free(exit_status);
	return (result);
}

char	*add_whats_next(char *str, int i, char *result)
{
	int		j;
	char	*tmp;

	j = i;
	while (str[j])
		j++;
	j--;
	if (str[j])
	{
		tmp = ft_substr(str, i + 1, j - i + 1);
		result = ft_strjoin(result, tmp);
		free(tmp);
	}
	return (result);
}

char	*is_empty_var(char *result)
{
	char	*tmp_result;

	tmp_result = "$";
	if (result)
		free(result);
	return (tmp_result);
}

char	*add_env_var(char *result, char *find_var)
{
	char	*tmp;

	if (find_var)
	{
		tmp = ft_strjoin(result, find_var);
		if (result)
			free(result);
		result = tmp;
	}
	return (result);
}

char	*add_env_var_next(char *var, int i, char *result)
{
	char	*tmp;
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
