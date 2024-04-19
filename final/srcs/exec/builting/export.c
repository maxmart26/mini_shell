/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/19 15:17:56 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

int	ft_strlen_export(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_expor_ex(char *tmp, t_data *data)
{
	t_env	*init;

	init = data->env;
	while (init)
	{
		if (ft_strncmp(init->value, tmp, ft_strlen_export(tmp, '=')) == 0)
		{
			ft_export_modif(tmp, init);
			return (0);
		}
		init = init->next;
	}
	return (1);
}

void	ft_export_2(char **strs, t_data *data)
{
	t_env	*current;

	if (ft_expor_ex(strs[1], data) == 1)
	{
		if (!data->env)
		{
			data->env = new_env();
			data->env->value = ft_strdup(strs[1]);
		}
		else
		{
			current = data->env;
			while (current->next)
				current = current->next;
			current->next = new_env();
			if (!current->next)
			{
				return ;
			}
			current->next->value = ft_strdup(strs[1]);
			current->next->prev = current;
			while (data->env->prev)
				data->env = data->env->prev;
		}
	}
}

int	verif_export(char **str, t_data *data)
{
	int		i;
	char	**strs;

	strs = ft_split(str[1], '=');
	i = 0;
	if (strs[0] == NULL)
	{
		ft_printf_error(" not a valid identifier\n");
		ft_free_tab(strs);
		free_tab(str);
		data->exit = 1;
		return (1);
	}
	while (strs[0][i])
	{
		if (strs[0][i] == '@' || strs[0][i] == '_' || strs[0][i] == '-'
			|| strs[0][i] == '\\' || strs[0][i] == '%' || strs[0][i] == '+'
			|| (strs[0][i] == '=' && strs[0][i + 1] == '\0') || (strs[0][i] <= '9' && strs[0][i] >= '0'))
		{
			ft_printf_error("bash: export: `%s': not a valid identifier\n",
				str[1]);
			ft_free_tab(strs);
			free_tab(str);
			data->exit = 1;
			return (1);
		}
		i++;
	}
	ft_free_tab(strs);
	return (0);
}

void	ft_export(char **strs, t_data *data, int i)
{
	if (i == 0)
	{
		ft_end(data, strs);
		exit(156);
	}
	if (strs[1] == NULL)
		ft_trie_export(data);
	else if (verif_export(strs, data) == 1)
		return ;
	else
	{
		ft_export_2(strs, data);
	}
	data->exit = 0;
}
