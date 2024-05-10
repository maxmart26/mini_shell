/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:28 by matorgue          #+#    #+#             */
/*   Updated: 2024/05/10 11:59:28 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_include.h"
#include "../../../include/minishell_proto.h"
#include "../../../include/minishell_struct.h"

int		verif_export(char *str, t_data *data);

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

void	ft_export_3(char **strs, int i, t_data *data, t_env *current)
{
	if (verif_export(strs[i], data) == 1)
		data->exit = 552;
	else if (ft_expor_ex(strs[i], data) == 1)
	{
		if (!data->env)
		{
			data->env = new_env();
			data->env->value = ft_strdup(strs[i]);
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
			current->next->value = ft_strdup(strs[i]);
			current->next->prev = current;
			while (data->env->prev)
				data->env = data->env->prev;
		}
	}
}

void	ft_export_2(char **strs, t_data *data)
{
	t_env	*current;
	int		i;

	i = 0;
	current = NULL;
	while (strs[i])
	{
		ft_export_3(strs, i, data, current);
		i++;
	}
}

int	verif_export(char *str, t_data *data)
{
	int		i;
	char	**strs;

	strs = ft_split(str, '=');
	i = 0;
	if (strs[0] == NULL)
	{
		ft_printf_error(" not a valid identifier\n");
		ft_free_tab(strs);
		data->exit = 552;
		return (1);
	}
	while (strs[0][i])
	{
		if (verif_export_acsii(strs[0][i], str, data) == 1)
		{
			ft_free_tab(strs);
			return (1);
		}
		i++;
	}
	ft_free_tab(strs);
	return (0);
}

void	ft_export(char **strs, t_data *data, int i, t_token *token)
{
	if (i == 0)
	{
		if (strs[1] == NULL)
			ft_trie_export(data, token, 1);
		ft_end(data);
		exit(199);
	}
	if (strs[1] == NULL)
		ft_trie_export(data, token, 0);
	else
	{
		ft_export_2(strs, data);
	}
	if (data->exit == 552)
		data->exit = 1;
	else
		data->exit = 0;
	if (i > 0)
	{
		ft_end(data);
		exit(0);
	}
}
