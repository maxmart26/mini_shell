/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/16 18:33:29 by matorgue         ###   ########.fr       */
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

int	verif_export(char **str)
{
	int	i;

	i = 0;
	while (str[1][i])
	{
		if (str[1][i] == '@' || str[1][i] == '_'
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
	if (i == 0)
	{
		ft_end(data, strs);
		exit(156);
	}
	if (strs[1] == NULL)
		ft_trie_export(data);
	else if (verif_export(strs) == 1)
		return ;
	else
	{
		ft_export_2(strs, data);
	}
}
