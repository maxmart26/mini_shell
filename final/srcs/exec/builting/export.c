/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/10 18:35:18 by matorgue         ###   ########.fr       */
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
	str = ft_split(strs[1], '=');
	if (ft_expor_ex(strs[1], data, str) == 1)
	{
		if (!data->env)
		{
			data->env = new_env();
			data->env->value = strs[1];
			data->env->content = str[1];
			data->env->name = str[0];
			free_tab(str);
		}
		else
		{
			while (data->env->next)
				data->env = data->env->next;
			data->env->next = new_env();
			data->env->next->value = strs[1];
			data->env->next->prev = data->env;
			data->env->next->content = str[1];
			data->env->next->name = str[0];
			free(str);
			while (data->env->prev)
				data->env = data->env->prev;
		}
	}
}

int	verif_export(char **str)
{
	int	i;

	i = 0;
	while (str[1][i])
	{
		if (str[1][i] == '@' || str[1][i] == '_' || str[1][i] == '.'
			|| str[1][i] == '\\' || str[1][i] == '%' || str[1][i] == '+'
			|| (str[1][i] == '=' && str[1][i + 1] == '\0'))
		{
			ft_printf_error("bash: export: `%s': not a valid identifier\n", str[1]);
			free_tab(str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(char **strs, t_data *data, int i)
{
	char	**str;

	str = NULL;
	if (i == 0)
		exit(156);
	if (strs[1] == NULL)
		ft_trie_export(data);
	else if (verif_export(strs) == 1)
		return ;
	else
		ft_export_2(strs, data, str);
	// if (strs)
	// 	free_tab(strs);
}
