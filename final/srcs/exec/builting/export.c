/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnunez-t <lnunez-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/13 18:33:15 by lnunez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

int	ft_expor_ex(char *tmp, t_data *data, char **str)
{
	t_env	*init;

	init = data->env;
	while (init)
	{
		if (ft_strncmp(init->name, str[0], ft_strlen(str[0])) == 0
			&& ft_strlen(str[0]) == ft_strlen(init->name))
		{
			ft_export_modif(tmp, init, str);
			return (0);
		}
		init = init->next;
	}
	return (1);
}

void	ft_export_2(char **strs, t_data *data, char **str)
{
	char	*name;
	char	*content;
	t_env	*current;

	str = ft_split(strs[1], '=');
	if (str && str[0] && str[1] && ft_expor_ex(strs[1], data, str) == 1)
	{
		name = strdup(str[0]);
		content = strdup(str[1]);
		if (!data->env)
		{
			data->env = new_env();
			data->env->value = ft_strdup(strs[1]);
			data->env->content = content;
			data->env->name = name;
		}
		else
		{
			current = data->env;
			while (current->next)
				current = current->next;
			current->next = new_env();
			if (!current->next)
			{
				free(name);
				free(content);
				return ;
			}
			current->next->value = ft_strdup(strs[1]);
			current->next->prev = current;
			current->next->content = content;
			current->next->name = name;
			while (data->env->prev)
				data->env = data->env->prev;
		}
		ft_free_tab(str);
	}
}

void	ft_export(char **strs, t_data *data, int i)
{
	char	**str;

	str = NULL;
	if (i == 0)
		exit(156);
	if (strs[1] == NULL)
		ft_trie_export(data);
	else
	{
		ft_export_2(strs, data, str);
	}
}
